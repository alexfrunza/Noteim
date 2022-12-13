#include <graphics.h>
#include <cmath>
#include <stdio.h>

#include "editor.h"
#include "helpers.h"

#include <iostream>
using namespace std;

MenuArea* initMenuArea(Point topLeft, Point bottomRight)
{
    MenuArea* ma = new MenuArea;
    return ma;
}

void drawArea(MenuArea *ma)
{
}

ScrollBarsArea* initScrollBarsArea(Point topLeft, Point bottomRight)
{
}

void drawArea(ScrollBarsArea *sba)
{
}

Cursor *initCursor(Point position)
{
    Cursor* c = new Cursor;
    c->position = position;
    c->positionInNode = 0;

    return c;
}

TextArea* initTextArea(Point topLeft, Point bottomRight)
{
    TextArea* ta = new TextArea;
    ta->unixFile = false;

    ta->cursor = initCursor(topLeft);
    ta->topLeft = topLeft;
    ta->bottomRight = bottomRight;
    ta->cursor = initCursor(topLeft);
    ta->firstLine = 0;
    drawCursorLine(ta->cursor->position);

    ta->changes = true;
    ta->pieceTable = initPieceTable();
    Buffer *firstBuffer = initBuffer();
    addBuffer(ta->pieceTable->buffersList, firstBuffer);
    PieceTableNode *firstNode = initPieceTableNode(ta->pieceTable->buffersList->first,0,0,0);
    addPieceTableNode(ta->pieceTable->nodesList,firstNode);
    ta->cursor->pieceTableNode = ta->pieceTable->nodesList->first;
    ta->maxLines = abs(bottomRight.y - topLeft.y) / CHAR_HEIGHT;
    ta->maxCharLine = abs(bottomRight.x - topLeft.x) / CHAR_WIDTH;

    return ta;
}

TextArea* initTextArea(Point topLeft, Point bottomRight, char *fileName)
{
    TextArea* ta = new TextArea;
    ta->unixFile = false;
    ta->changes = true;
    ta->firstLine = 0;

    ta->topLeft = topLeft;
    ta->bottomRight = bottomRight;

    ta->pieceTable = initPieceTable();

    ta->maxLines = abs(bottomRight.y - topLeft.y) / CHAR_HEIGHT;
    ta->maxCharLine = abs(bottomRight.x - topLeft.x) / CHAR_WIDTH;

    openFile(ta, fileName);
    ta->cursor = initCursor(topLeft);
    drawCursorLine(ta->cursor->position);
    ta->cursor->pieceTableNode = ta->pieceTable->nodesList->first;
    return ta;
}

void drawCursorLine(Point p, bool white)
{
    if(white==true)
        setcolor(WHITE);
    line(p.x*CHAR_WIDTH,p.y*CHAR_HEIGHT,p.x*CHAR_WIDTH,p.y*CHAR_HEIGHT+CHAR_HEIGHT-1);
    setcolor(BLACK);
}

void getCursorPositionInPiecetable(PieceTable *pt, Cursor *c, int firstLine, Point dest)
{
    // Trebuie modificat sa tina cont si de offset-ul pe linie (x)
    PieceTableNode *ptn = pt->nodesList->first;
    int remainingNewLines = dest.y + firstLine, i, currentXInLine=0;
    while(ptn!=NULL)
    {
        if(remainingNewLines-(int)ptn->numberNewLines<=0)
            break;
        remainingNewLines -= ptn->numberNewLines;
        ptn = ptn->next;
    }
    if(ptn==NULL)
    {
        ptn = pt->nodesList->last;
        i = ptn->start+ptn->length-1;
        while(ptn!=NULL && ptn->buffer->text[i]!='\n')
        {
            if(i==ptn->start-1)
            {
                ptn = ptn->prev;
                if(ptn!=NULL)
                    i = ptn->start+ptn->length+1;
            }
            else
                currentXInLine++;
            i--;
        }
        c->position = {currentXInLine,dest.y-remainingNewLines};
        c->pieceTableNode = pt->nodesList->last;
        c->positionInNode = pt->nodesList->last->length-1;
        return;
    }
    i = ptn->start;
    while(remainingNewLines!=0)
    {
        if(ptn->buffer->text[i]=='\n')
            remainingNewLines--;
        i++;
    }
    while(ptn!=NULL && currentXInLine!=dest.x && ptn->buffer->text[i]!='\n')
    {
        if(i==ptn->start+ptn->length)
        {
            ptn = ptn->next;
            if(ptn!=NULL)
                i = ptn->start-1;
        }
        else
            currentXInLine++;
        i++;
    }
    if(currentXInLine==dest.x)
    {
        c->position = dest;
        c->pieceTableNode = ptn;
        c->positionInNode = i-ptn->start;
    }
    else
    {
        c->position = {currentXInLine,dest.y};
        if(ptn==NULL)
        {
            c->pieceTableNode = pt->nodesList->last;
            c->positionInNode = i-pt->nodesList->last->start-1;
        }
        else
        {
            c->pieceTableNode = ptn;
            c->positionInNode = i-ptn->start;
        }
    }
}

void moveCursor(TextArea *ta, Point dest)
{
    if(ta->pieceTable->nodesList->length==0)
        return;
    if(dest.x<0)
    {
        // De facut
        // if(ta.firstColumn>0)
        //     scrollLeft
        return;
    }
    if(dest.y<0)
    {
        // De facut
        // if(ta.firstLine>0)
        //     scrollUp
        return;
    }
    if(dest.x>=ta->maxCharLine)
    {
        // De facut
        // Conditie??
        // scrollRight
        return;
    }
    if(dest.y>=ta->maxLines)
    {
        // De facut
        // if(dest.y<=ta->pieceTable->numberOfLines)
        // scrollDown
        return;
    }

    drawCursorLine(ta->cursor->position,true);
    getCursorPositionInPiecetable(ta->pieceTable,ta->cursor,ta->firstLine,dest);
    drawCursorLine(ta->cursor->position);
}

void moveCursorByArrow(TextArea *ta, char a)
{
    Point dest = ta->cursor->position;
    switch(a)
    {
    case 72: // Sus
        dest.y--;
        break;
    case 80: // Jos
        dest.y++;
        break;
    case 75: // Stanga
        dest.x--;
        break;
    case 77: // Dreapta
        dest.x++;
    }
    moveCursor(ta,dest);
}

Editor* initEditor()
{
    initwindow(MAX_WIDTH,MAX_HEIGHT,"Notepad Improved");
    settextstyle(0, HORIZ_DIR, 2);

    setbkcolor(WHITE);
    setcolor(BLACK);
    cleardevice();

    Editor *e = new Editor;
    e->running = true;

    Point topLeft, bottomRight;

    topLeft= {0, 0};
    bottomRight = {MAX_WIDTH,MAX_HEIGHT};
    e->menuArea = initMenuArea(topLeft, bottomRight);

    topLeft= {0,0};
    bottomRight = {MAX_WIDTH,MAX_HEIGHT};
    //e->scrollBarsArea = initScrollBarsArea(topLeft, bottomRight);
    // De mutat in initTextArea

    topLeft= {0, 0};
    bottomRight = {MAX_WIDTH,MAX_HEIGHT};

    // !!!!!!!!!!!!!!!!!!!!!!!!
    // Citire din fisier
    //cout<<"TOP LEFT: "<<topLeft.x<<" "<<topLeft.y<<'\n';
    //cout<<"RIGHT BOTTOM: "<<bottomRight.x<<" "<<bottomRight.y<<'\n';


    e->textArea = initTextArea(topLeft, bottomRight, "textText.txt");
    // e->textArea = initTextArea(topLeft, bottomRight);

    return e;
}

void drawCharsInGui(Buffer* b, int x, int y, long index, long endOfDisplayedLine)
{
    char aux = b->text[endOfDisplayedLine];
    b->text[endOfDisplayedLine] = '\0';
    //cout<<"SIr afisat: "<<index<<" "<<endOfDisplayedLine<<endl;
    outtextxy(x, y, b->text + index);
    b->text[endOfDisplayedLine] = aux;
}

void showALine(int y, TextArea* ta, PieceTableNode* ptn, long indexOfLine)
{
    long numberOfCharsFromNode;
    long spaceRemainedOnScreen = ta->maxCharLine - 1;
    long current_x = ta->topLeft.x;
    long endOfDisplayedLine;
    long skippedChars = ta->firstColumn;
    bool lineEnded = false;
    bool skippedNode;

    while(spaceRemainedOnScreen > 0 && !lineEnded && ptn != NULL)
    {
        numberOfCharsFromNode = ptn->length - (indexOfLine - ptn->start);
        endOfDisplayedLine = indexOfLine + numberOfCharsFromNode;
        skippedNode = false;

        // For horizontal scroll
        if(skippedChars > 0)
        {
            if(numberOfCharsFromNode <= spaceRemainedOnScreen)
            {
                endOfDisplayedLine = indexOfLine + numberOfCharsFromNode;
            }
            else
            {
                endOfDisplayedLine = indexOfLine + spaceRemainedOnScreen;
            }

            char aux = ptn->buffer->text[endOfDisplayedLine];
            ptn->buffer->text[endOfDisplayedLine] = '\0';
            char *newLineInNode = strchr(ptn->buffer->text + indexOfLine, '\n');
            ptn->buffer->text[endOfDisplayedLine] = aux;

            if(newLineInNode)
            {
                numberOfCharsFromNode -= endOfDisplayedLine - (newLineInNode - ptn->buffer->text + 1);
                endOfDisplayedLine = newLineInNode - ptn->buffer->text + 1;
                lineEnded = true;
            }

            if(numberOfCharsFromNode <= skippedChars)
            {
                numberOfCharsFromNode = 0;
                skippedChars = skippedChars - numberOfCharsFromNode;
                skippedNode = true;
            }
            else
            {
                numberOfCharsFromNode -= skippedChars;
                indexOfLine += skippedChars;
                skippedChars = 0;
            }
        }
        // end

        if(numberOfCharsFromNode <= spaceRemainedOnScreen && !skippedNode)
        {
            endOfDisplayedLine = indexOfLine + numberOfCharsFromNode;

            char aux = ptn->buffer->text[endOfDisplayedLine];
            ptn->buffer->text[endOfDisplayedLine] = '\0';
            char *newLineInNode = strchr(ptn->buffer->text + indexOfLine, '\n');
            ptn->buffer->text[endOfDisplayedLine] = aux;

            if(newLineInNode)
            {
                numberOfCharsFromNode -= endOfDisplayedLine - (newLineInNode - ptn->buffer->text + 1);
                endOfDisplayedLine = newLineInNode - ptn->buffer->text + 1;
                lineEnded = true;
                //cout<<"INDEXXXX: "<<indexOfLine<<" "<<endOfDisplayedLine<<endl;
            }

            //cout<<"DE la caracter mai mic: "<<indexOfLine<<" "<<endOfDisplayedLine<<endl;
            spaceRemainedOnScreen -= numberOfCharsFromNode;
            drawCharsInGui(ptn->buffer, current_x, y, indexOfLine, endOfDisplayedLine);
            current_x += numberOfCharsFromNode * CHAR_WIDTH;
        }
        else if(!skippedNode)
        {
            endOfDisplayedLine = indexOfLine + spaceRemainedOnScreen;

            char aux = ptn->buffer->text[endOfDisplayedLine];
            ptn->buffer->text[endOfDisplayedLine] = '\0';
            char *newLineInNode = strchr(ptn->buffer->text + indexOfLine, '\n');
            ptn->buffer->text[endOfDisplayedLine] = aux;

            if(newLineInNode)
            {
                endOfDisplayedLine = newLineInNode - ptn->buffer->text + 1;
                lineEnded = true;
            }

            //cout<<"DE la caracter mai mare: "<<indexOfLine<<" "<<endOfDisplayedLine<<endl;
            drawCharsInGui(ptn->buffer, current_x, y, indexOfLine, endOfDisplayedLine);
            lineEnded = true;
        }

        ptn = ptn->next;
        if(ptn != NULL) indexOfLine = ptn->start;
    }
}

void drawArea(TextArea *ta)
{
    if(ta->changes==false)
        return;

    int current_y=ta->topLeft.y;

    setfillstyle(1, COLOR(255, 255, 255));
    bar(ta->topLeft.x, ta->topLeft.y, ta->bottomRight.x, ta->bottomRight.y);

    long showedLines = 0;
    long currentLine = ta->firstLine;

    while(showedLines < ta->maxLines)
    {
        PieceTableNode* lineNode;
        long indexOfLine;

        getWhereLineStarts(ta->pieceTable, currentLine, lineNode, indexOfLine);
        if(!lineNode)
        {
            //cout<<"NU exista linia: "<<showedLines<<endl;
            break;
        }

        //cout<<"LINIA: "<<showedLines<<endl;
        //cout<<"*****: "<< indexOfLine<<"   "<<lineNode<<endl;
        showALine(current_y, ta, lineNode, indexOfLine);

        current_y += CHAR_HEIGHT;
        currentLine++;
        showedLines++;
    }
    drawCursorLine(ta->cursor->position);
}

void openFile(TextArea *ta, char *fileName)
{
    FILE *file = fopen(fileName, "rb");

    if(file == NULL)
    {
        fclose(file);
        printf("Eroare la citirea fisierului!\n");
        return;
    }

    emptyPieceTable(ta->pieceTable);

    bool unixFile = false;
    unsigned int readSize;
    do
    {
        Buffer *newBuffer = initBuffer();
        addBuffer(ta->pieceTable->buffersList, newBuffer);
        newBuffer->length = 0;

        unsigned int numberNewLines = 0;
        char x, last_x;

        fread(&last_x, sizeof(char), 1, file);
        newBuffer->text[newBuffer->length] = last_x;
        if(last_x == '\n')
        {
            numberNewLines++;
            unixFile = true;
        }
        newBuffer->length++;

        while((newBuffer->length < MAX_LENGTH_BUFFER) && fread(&x, sizeof(char), 1, file))
        {
            newBuffer->text[newBuffer->length] = x;
            if(x == '\n') numberNewLines++;
            if(x == '\n' && last_x != '\r') unixFile = true;
            if(x == '\n' && last_x == '\r')
            {
                newBuffer->length--;
                newBuffer->text[newBuffer->length] = x;
            }
            newBuffer->length++;
            last_x = x;
        }
        PieceTableNode *newNode = initPieceTableNode(newBuffer, 0, newBuffer->length, numberNewLines);
        addPieceTableNode(ta->pieceTable->nodesList, newNode);
        ta->pieceTable->numberOfLines += numberNewLines;

        //cout<<"lungimE buffer: "<<newBuffer->length<<"CARACTER: *"<<(int)newBuffer->text[0]<<"*"<<endl;
        readSize = newBuffer->length;

        /*if(newBuffer->length == 1 && newBuffer->text[0] == '\0') {
            emptyPieceTable(ta->pieceTable);
        }*/
    }
    while(readSize == MAX_LENGTH_BUFFER);

    if(unixFile) ta->unixFile = true;
    Buffer *newBuffer = initBuffer();
    addBuffer(ta->pieceTable->buffersList, newBuffer);

    fclose(file);
}

void saveFile(TextArea *ta, char *fileName)
{
}

void drawEditor(Editor *e)
{
    drawArea(e->textArea);
    //drawArea(e->menuArea);
    //drawArea(e->scrollBarsArea);
    e->textArea->changes = false;
}

void stopEditor(Editor *e)
{
    e->running = false;
    closegraph();
    // TODO: Delete data from memory
}
