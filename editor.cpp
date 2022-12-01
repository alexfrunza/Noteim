#include <graphics.h>
#include <cmath>

#include "editor.h"
#include "helpers.h"

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

TextArea* initTextArea(Point topLeft, Point bottomRight)
{
    TextArea* ta = new TextArea;
    ta->topLeft = ta->cursorPosition = topLeft;
    ta->bottomRight = bottomRight;
    drawCursorLine(ta->cursorPosition);
    ta->changes = true;
    ta->pieceTable = initPieceTable();
    Buffer *newBuffer = initBuffer();
    addBuffer(ta->pieceTable->buffersList, newBuffer);
    ta->maxLines = abs(bottomRight.y - topLeft.y) / CHAR_HEIGHT;
    ta->maxCharLine = abs(bottomRight.x - topLeft.x) / CHAR_WIDTH;
    return ta;
}

TextArea* initTextArea(Point topLeft, Point bottomRight, char *fileName)
{
    TextArea* ta = new TextArea;
    ta->topLeft = ta->cursorPosition = topLeft;
    ta->bottomRight = bottomRight;
    drawCursorLine(ta->cursorPosition);
    ta->changes = true;
    ta->pieceTable = initPieceTable();
    ta->cursorPosition={0,0};
    ta->maxLines = abs(bottomRight.y - topLeft.y) / CHAR_HEIGHT;
    ta->maxCharLine = abs(bottomRight.x - topLeft.x) / CHAR_WIDTH;
    // De facut
    return ta;
}

void drawCursorLine(Point p, bool white)
{
    if(white==true)
        setcolor(WHITE);
    line(p.x*CHAR_WIDTH,p.y*CHAR_HEIGHT,p.x*CHAR_WIDTH,p.y*CHAR_HEIGHT+CHAR_HEIGHT-1);
    setcolor(BLACK);
}

void moveCursor(TextArea *ta, Point dest)
{
    if(dest.x<0 || dest.y <0)
        return;
    if(dest.x>=ta->maxCharLine || dest.y>=ta->maxLines)
        return;
    ta->changes = true;
    drawCursorLine(ta->cursorPosition,true);
    PieceTableNode *ptn = ta->pieceTable->nodesList->first;
    int remainingNewLines = dest.y, i, currentXInLine=0;
    while(ptn!=NULL)
    {
        if(remainingNewLines-(int)ptn->numberNewLines<=0)
            break;
        remainingNewLines -= ptn->numberNewLines;
        ptn = ptn->next;
    }
    if(ptn==NULL)
    {
        ptn = ta->pieceTable->nodesList->last;
        i = ptn->start+ptn->length-1;
        currentXInLine = 0;
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
        ta->cursorPosition = {currentXInLine,dest.y-remainingNewLines};
        drawCursorLine(ta->cursorPosition);
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
    if(ptn==NULL || ptn->buffer->text[i]=='\n')
        ta->cursorPosition = {currentXInLine,dest.y};
    else
        ta->cursorPosition = dest;
    drawCursorLine(ta->cursorPosition);
}

void moveCursorByArrow(TextArea *ta, char a)
{
    Point dest = ta->cursorPosition;
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
    settextstyle(0, HORIZ_DIR, 1);

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

    int current_x=0, current_y=0;
    char *posInBuffer, *newLinePosInBuffer, aux;
    unsigned int newLinesRemaining;
    PieceTableNode *currentPTN = ta->pieceTable->nodesList->first;
    while(currentPTN!=NULL)
    {
        newLinesRemaining = currentPTN->numberNewLines;
        posInBuffer = currentPTN->buffer->text+currentPTN->start;
        while(newLinesRemaining)
        {
            newLinePosInBuffer = strchr(posInBuffer+currentPTN->start,'\n');
            newLinePosInBuffer[0]='\0';
            outtextxy(current_x,current_y,posInBuffer);
            newLinePosInBuffer[0]='\n';
            current_x = 0;
            current_y += CHAR_HEIGHT;
            posInBuffer = newLinePosInBuffer+1;
            newLinesRemaining--;
        }
        aux = currentPTN->buffer->text[currentPTN->start+currentPTN->length];
        currentPTN->buffer->text[currentPTN->start+currentPTN->length] = '\0';
        outtextxy(current_x,current_y,posInBuffer);
        currentPTN->buffer->text[currentPTN->start+currentPTN->length] = aux;
        currentPTN = currentPTN->next;
    }
    drawCursorLine(ta->cursorPosition);
}

void drawEditor(Editor *e)
{
    //drawArea(e->menuArea);
    //drawArea(e->scrollBarsArea);
    drawArea(e->textArea);
    e->textArea->changes = false;
}

void stopEditor(Editor *e)
{
    e->running = false;
    closegraph();
    // Delete data from memory
}
