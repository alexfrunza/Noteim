#include <graphics.h>
#include "piecetable.h"
#include "color.h"

#ifndef NOTEIM_EDITOR_H
#define NOTEIM_EDITOR_H

#define MAX_WIDTH getmaxwidth()
#define MAX_HEIGHT getmaxheight()
#define MAX_NAMES_LEN 50

struct Button {
    char *text;
    int type;
    bool hovered;
    bool changes;
    unsigned int padding;

    Color hoverBK;
    Color normalBK;
    Color hoverFT;
    Color normalFT;

    Point topLeft;
    Point bottomRight;

    Button *next;
    Button *prev;
};

Button* initButton(char *name, Point topLeft);
void drawButton(Button* b);


struct ButtonsList {
    Button *first;
    Button *last;
    unsigned int length;
};

ButtonsList* initButtonsList(char buttonsNames[][MAX_NAMES_LEN], unsigned int length);
void removeLastButtonFromList(ButtonsList *bl);
void clearButtonsList(ButtonsList *bl);
void addButtonToList(ButtonsList *bl, Button *b);
bool isButtonsListEmpty(ButtonsList *bl);
void drawButtonsList(ButtonsList *bl);

struct MenuArea
{
    bool changes;
    Point topLeft;
    Point bottomRight;
    unsigned int separatorLength;

    ButtonsList* buttonsList;
    // Soon
};

MenuArea* initMenuArea(Point topLeft);
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

struct Cursor
{
    Point position;

    unsigned int positionInPieceTable;

    PieceTableNode* pieceTableNode;
    unsigned int positionInNode;
};

Cursor* initCursor();
void getCursorPositionInPiecetable(PieceTable *pt, Cursor &c, int firstLine, Point dest);

struct TextArea
{
    bool changes;
    // De implementat la salvare, corespunzator pentru Windows file si unixFile (asaugare '\r' pentru windows file)
    bool unixFile;
    bool savedChanges;

    unsigned int maxLines;
    unsigned short int maxCharLine;
    Point topLeft;
    Point bottomRight;

    Cursor *cursor;
    // Absolute number of the first line to be displayed on screen
    unsigned int firstLine;
    unsigned int firstColumn;

    PieceTable *pieceTable;
    ScrollBarsArea *scrollBarsArea;
    // Memorez fila in care lucrez curent, daca e deschisa, sa stiu sa salvez tot in ea.
};

TextArea* initTextArea(Point topLeft, Point bottomRight);
TextArea* initTextArea(Point topLeft, Point bottomRight, char *fileName);
void drawArea(TextArea *ta);
void drawCursorLine(Point p, bool white=false);
void moveCursor(TextArea *ta, Point dest);
void moveCursorByArrow(TextArea *ta, char a);
void openFile(TextArea *ta, char *fileName);
void saveFile(TextArea *ta, char *fileName);

struct Editor
{
    bool running;
    MenuArea *menuArea;
    TextArea *textArea;
};

Editor* initEditor();
void drawEditor(Editor *e);
void stopEditor(Editor *e);

#endif // NOTEIM_EDITOR_H
