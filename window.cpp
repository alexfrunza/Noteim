#include "window.h"
#include <graphics.h>

Window* initializeWindow()
{
    initwindow(MAX_WIDTH,MAX_HEIGHT,"Notepad Improved");
    setbkcolor(WHITE);
    setcolor(BLACK);
    cleardevice();
    Window *w = new Window;
    w->menu = new MenuArea;
    w->scrollBars = new ScrollBarsArea;
    w->text = new TextArea;
    w->text->topLeft={0,0};
    w->text->bottomRight={MAX_WIDTH,MAX_HEIGHT};
    w->text->pieceTable = initPieceTable();
    return w;
}

void drawText(Window *w)
{
    // Soon
}
