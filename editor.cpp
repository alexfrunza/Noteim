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

    ta->maxLines = abs(bottomRight.y - topLeft.y) / textheight("|");
    ta->maxCharLine = abs(bottomRight.x - topLeft.x) / textwidth("m");
    // De facut
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

    topLeft.x = 0;
    topLeft.y = 0;
    bottomRight.x = MAX_WIDTH;
    bottomRight.y = MAX_HEIGHT;
    e->menuArea = initMenuArea(topLeft, bottomRight);

    topLeft.x = 0;
    topLeft.y = 0;
    bottomRight.x = MAX_WIDTH;
    bottomRight.y = MAX_HEIGHT;
    e->scrollBarsArea = initScrollBarsArea(topLeft, bottomRight);

    topLeft.x = 0;
    topLeft.y = 0;
    bottomRight.x = MAX_WIDTH;
    bottomRight.y = MAX_HEIGHT;
    e->textArea = initTextArea(topLeft, bottomRight);

    return e;
}

void drawArea(TextArea *ta)
{
    if(ta->changes == false)
    {
        return;
    }
}

void drawEditor(Editor *e)
{
    drawArea(e->menuArea);
    drawArea(e->scrollBarsArea);
    drawArea(e->textArea);
}

void stopEditor(Editor *e)
{
    e->running = false;
    closegraph();
    // Delete data from memory
}
