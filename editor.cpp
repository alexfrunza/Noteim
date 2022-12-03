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

// De facut
Cursor *initCursor(Point position)
{
    Cursor* c = new Cursor;
    c->position = position;

    return c;
}

TextArea* initTextArea(Point topLeft, Point bottomRight)
{
    TextArea* ta = new TextArea;
    ta->topLeft = topLeft;
    ta->cursor = initCursor(topLeft);
    ta->firstLine = 0;

    ta->bottomRight = bottomRight;
    drawCursorLine(ta->cursor->position);
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
    ta->topLeft = ta->cursor->position = topLeft;
    ta->cursor = initCursor(topLeft);
    ta->firstLine = 0;

    ta->bottomRight = bottomRight;
    drawCursorLine(ta->cursor->position);
    ta->changes = true;
    ta->pieceTable = initPieceTable();
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
    if(ta->pieceTable->nodesList->length==0)
        return;

    drawCursorLine(ta->cursor->position,true);
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
        ta->cursor->position = {currentXInLine,dest.y-remainingNewLines};
        drawCursorLine(ta->cursor->position);
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
        ta->cursor->position = {currentXInLine,dest.y};
    else
        ta->cursor->position = dest;
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
                    for(unsigned int i = positionInText; i < positionNewline && i < maxPosition; i++, current_x += CHAR_WIDTH)
                    {
                        char aux = currentPtn->buffer->text[i+1];
                        currentPtn->buffer->text[i+1] = '\0';
                        outtextxy(current_x,current_y,currentPtn->buffer->text + i);
                        currentPtn->buffer->text[i+1] = aux;
                    }

                    current_x = ta->topLeft.x;
                    current_y += CHAR_HEIGHT;
                    drawCursorLine({current_x,current_y},true);

                    positionInText = newLineInNode - currentPtn->buffer->text + 1;
                    linesRemainedToDisplay--;
                    if(linesRemainedToDisplay == 0) linesDisplayed = true;
                }
                else
                {
                    unsigned int maxPosition = positionInText + ta->maxCharLine;
                    for(unsigned int i = positionInText; i <= maxIndexInNode && i < maxPosition; i++, current_x += CHAR_WIDTH)
                    {
                        char aux = currentPtn->buffer->text[i+1];
                        currentPtn->buffer->text[i+1] = '\0';
                        outtextxy(current_x,current_y,currentPtn->buffer->text + i);
                        currentPtn->buffer->text[i+1] = aux;
                    }

                    positionInText = maxIndexInNode+1;
                }
            }

            currentPtn = currentPtn->next;
        }
    }
    drawCursorLine(ta->cursor->position);
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
