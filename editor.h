#include <graphics.h>
#include "piecetable.h"
#include "helpers.h"

#ifndef NOTEIM_EDITOR_H
#define NOTEIM_EDITOR_H

#define MAX_WIDTH getmaxwidth()
#define MAX_HEIGHT getmaxheight()

struct MenuArea
{
    bool changes;
    // Soon
};

MenuArea* initMenuArea(Point topLeft, Point bottomRight);
void drawArea(MenuArea *ma);

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
    bool changes;
    VerticalScrollBarArea verticalScrollBar;
    HorizontalScrollBarArea horizontalScrollBar;
};

ScrollBarsArea* initScrollBarsArea(Point topLeft, Point bottomRight);
void drawArea(ScrollBarsArea *sba);

struct TextArea
{
    bool changes;
    unsigned int maxLines;
    unsigned short int maxCharLine;
    Point topLeft;
    Point bottomRight;
    PieceTable *pieceTable;
};

TextArea* initTextArea(Point topLeft, Point bottomRight);
TextArea* initTextArea(Point topLeft, Point bottomRight, char *fileName);
void drawArea(TextArea *ta);

struct Editor
{
    bool running;
    MenuArea *menuArea;
    ScrollBarsArea *scrollBarsArea;
    TextArea *textArea;
};

Editor* initEditor();
void drawEditor(Editor *e);
void stopEditor(Editor *e);

#endif // NOTEIM_EDITOR_H