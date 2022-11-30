#include <graphics.h>
#include "piecetable.h"

#ifndef NOTEIM_WINDOW_H
#define NOTEIM_WINDOW_H

#define MAX_WIDTH getmaxwidth()
#define MAX_HEIGHT getmaxheight()

struct Point
{
    int x;
    int y;
};

struct MenuArea
{
    // Soon
};

struct VerticalScrollBarArea
{
    // Soon
};

struct HorizontalScrollBarArea
{
    // Soon
};

struct ScrollBarsArea
{
    VerticalScrollBarArea verticalScrollBar;
    HorizontalScrollBarArea horizontalScrollBar;
};

struct TextArea
{
    Point topLeft;
    Point bottomRight;
    PieceTable *pieceTable;
};

struct Window
{
    MenuArea *menu;
    ScrollBarsArea *scrollBars;
    TextArea *text;
};

Window* initializeWindow();
void drawText(Window *w);
void drawOverlay(Window *w);

#endif // NOTEIM_WINDOW_H
