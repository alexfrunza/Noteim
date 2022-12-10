#include <graphics.h>
#include <cmath>
#include <stdio.h>

#include "editor.h"
#include "helpers.h"

#include <iostream>
using namespace std;

MenuArea* initMenuArea(Point topLeft, Point bottomRight)
{
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

    // Pentru când ecranul e gol.
    if(ptn->length==0)
    {
        c->position = {0,0};
        c->pieceTableNode = ptn;
        c->positionInNode = 0;
        return;
    }

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

    topLeft= {0,0};
    bottomRight = {MAX_WIDTH,MAX_HEIGHT};
    e->menuArea = initMenuArea(topLeft, bottomRight);

    topLeft= {0,0};
    bottomRight = {MAX_WIDTH,MAX_HEIGHT};
    //e->scrollBarsArea = initScrollBarsArea(topLeft, bottomRight);
    // De mutat in initTextArea

    topLeft= {0,0};
    bottomRight = {MAX_WIDTH,MAX_HEIGHT};
    e->textArea = initTextArea(topLeft, bottomRight);

    return e;
}

void drawArea(TextArea *ta)
{
    if(ta->changes==false)
        return;

    int current_x=ta->topLeft.x;
    int current_y=ta->topLeft.y;

    setfillstyle(1, COLOR(255, 255, 255));
    bar(ta->topLeft.x, ta->topLeft.y, ta->bottomRight.x, ta->bottomRight.y);

    char *posInBuffer;
    char *newLinePosInBuffer;
    char aux;

    unsigned int newLinesRemaining;

    PieceTableNode *startPtn;
    unsigned int linesUntilStartPtn;

    if(ta->pieceTable->nodesList->first != NULL && ta->pieceTable->numberOfLines >= ta->firstLine)
    {
        getFirstNodeWhereAbsoluteLineIs(ta->pieceTable, ta->firstLine, startPtn, linesUntilStartPtn);

        unsigned int startIndex = startPtn->start;
        unsigned int newLinesCounter = linesUntilStartPtn;

        if(newLinesCounter < ta->firstLine)
        {
            while(newLinesCounter < ta->firstLine)
            {
                if(startPtn->buffer->text[startIndex] == '\n') newLinesCounter++;
                startIndex++;
            }
        }

        PieceTableNode* currentPtn = startPtn;
        unsigned int linesRemainedToDisplay = ta->maxLines;
        unsigned int positionInText = startIndex;
        bool linesDisplayed = false;
        bool skipUntilNextLine = false;
        unsigned int lenPrevSequence = 0;

        while(currentPtn!=NULL && !linesDisplayed)
        {
            long maxIndexInNode = currentPtn->start + currentPtn->length - 1;

            while((long)positionInText <= maxIndexInNode && !linesDisplayed)
            {
                char *newLineInNode = strchr(currentPtn->buffer->text + positionInText, '\n');
                if(newLineInNode)
                {
                    unsigned int positionNewline = newLineInNode - currentPtn->buffer->text;

                    unsigned int maxPosition = positionInText + ta->maxCharLine;

                    unsigned int position;
                    if(positionNewline > maxPosition)
                    {
                        position = maxPosition-1;
                    }
                    else position = positionNewline;

                    if(skipUntilNextLine == false)
                    {
                        char aux = currentPtn->buffer->text[position+1];
                        currentPtn->buffer->text[position+1] = '\0';
                        //cout<<currentPtn->buffer->text + positionInText<<'\n';
                        outtextxy(current_x,current_y,currentPtn->buffer->text + positionInText);
                        currentPtn->buffer->text[position+1] = aux;
                        current_x = ta->topLeft.x;
                        current_y += CHAR_HEIGHT;
                        linesRemainedToDisplay--;
                        if(linesRemainedToDisplay == 0) linesDisplayed = true;
                    }
                    if(skipUntilNextLine == true)
                    {
                        skipUntilNextLine = false;
                    }

                    drawCursorLine({current_x,current_y},true);

                    positionInText = positionNewline + 1;
                }
                else
                {
                    unsigned int maxPosition = positionInText + ta->maxCharLine;

                    unsigned int position;
                    if(maxIndexInNode > maxPosition)
                    {
                        position = maxPosition-1;
                    }
                    else position = maxIndexInNode;

                    int copyLenPrevSequence = lenPrevSequence;
                    if(current_x != ta->topLeft.x)
                    {
                        position -= lenPrevSequence;

                    }

                    if(skipUntilNextLine == false)
                    {
                        char aux = currentPtn->buffer->text[position+1];
                        currentPtn->buffer->text[position+1] = '\0';
                         //cout<<currentPtn->buffer->text + positionInText;
                        outtextxy(current_x,current_y,currentPtn->buffer->text + positionInText);
                        currentPtn->buffer->text[position+1] = aux;

                        current_x = CHAR_WIDTH*(position - positionInText + 1);
                        if(current_x != CHAR_WIDTH*maxPosition) lenPrevSequence = position - positionInText + 1;
                    }

                    if(maxPosition-1 == position + copyLenPrevSequence)
                    {
                        skipUntilNextLine = true;

                        current_y += CHAR_HEIGHT;
                        current_x = ta->topLeft.x;
                        linesRemainedToDisplay--;
                        lenPrevSequence = 0;
                        if(linesRemainedToDisplay == 0) linesDisplayed = true;
                    }

                    positionInText = maxIndexInNode+1;
                }
            }
            currentPtn = currentPtn->next;
            if(currentPtn != NULL) positionInText = currentPtn->start;
        }
        //cout<<endl<<"***********"<<endl;
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
        readSize = newBuffer->length;
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
    // Delete data from memory
}
