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
    ta->topLeft = topLeft;
    ta->bottomRight = bottomRight;
    ta->changes = true;

    ta->pieceTable = initPieceTable();

    Buffer *newBuffer = initBuffer();
    addBuffer(ta->pieceTable->buffersList, newBuffer);

    ta->maxLines = abs(bottomRight.y - topLeft.y) / textheight("|");
    ta->maxCharLine = abs(bottomRight.x - topLeft.x) / textwidth("m");
    return ta;
}

TextArea* initTextArea(Point topLeft, Point bottomRight, char *fileName)
{
    TextArea* ta = new TextArea;
    ta->topLeft = topLeft;
    ta->bottomRight = bottomRight;
    ta->changes = true;
    ta->pieceTable = initPieceTable();
    ta->cursorPosition={0,0};

    ta->maxLines = abs(bottomRight.y - topLeft.y) / CHAR_HEIGHT;
    ta->maxCharLine = abs(bottomRight.x - topLeft.x) / CHAR_WIDTH;
    // De facut
    return ta;
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

/*void drawArea(TextArea *ta)
{
    if(ta->changes == false)
        return;

    int current_x = 0, current_y = 0, i;
    char aux;
    Buffer *lastBuffer = ta->pieceTable->buffersList->last;
    for(i=0; i<lastBuffer->length; i++, current_x+=CHAR_WIDTH)
    {
        if(lastBuffer->text[i] == '\n')
        {
            current_y += CHAR_HEIGHT;
            current_x = -CHAR_WIDTH;
        }
        aux = lastBuffer->text[i+1];
        lastBuffer->text[i+1] = '\0';
        outtextxy(current_x, current_y, lastBuffer->text+i);
        lastBuffer->text[i+1] = aux;
    }
}*/

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
        posInBuffer = currentPTN->buffer->text;
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
}

void drawEditor(Editor *e)
{
    //drawArea(e->menuArea);
    //drawArea(e->scrollBarsArea);
    drawArea(e->textArea);
}

void stopEditor(Editor *e)
{
    e->running = false;
    closegraph();
    // Delete data from memory
}
