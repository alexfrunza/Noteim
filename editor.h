#include <graphics.h>
#include "piecetable.h"
#include "color.h"
#include <ctime>

#ifndef NOTEIM_EDITOR_H
#define NOTEIM_EDITOR_H

#define MAX_WIDTH getmaxwidth()
#define MAX_HEIGHT getmaxheight()
#define MAX_NAMES_LEN 50
#define MAX_CHAR_MODAL2_INPUT 30

struct Buton;
struct ButtonsList;
struct MenuArea;
struct Cursor;
struct TextArea;
struct Editor;
struct Modal1;
struct CursorModal2;
struct InputModal2;
struct Modal2;


enum ButtonType
{
    FILE_ACTIONS,
    EDIT,
    FORMAT,
    NEW_FILE,
    SAVE_FILE,
    SAVE_AS_FILE,
    OPEN_FILE,
    MODAL1_CONFIRM,
    MODAL1_CANCEL,
    MODAL2_CONFIRM,
    MODAL2_CANCEL
};

enum ButtonStyle
{
    MENUBAR,
    SUBMENU1,
    MODAL1_CONFIRM_STYLE,
    MODAL1_CANCEL_STYLE,
    MODAL2_CONFIRM_STYLE,
    MODAL2_CANCEL_STYLE
};

enum ButtonListStyle
{
    MENUBAR_BL,
    SUBMENU1_BL,
    MODAL1_BL,
    MODAL2_BL
};

struct Button
{
    char *text;
    ButtonType type;
    ButtonStyle style;


    bool hovered;
    bool changes;

    bool pressed;
    ButtonsList *subMenu;

    unsigned int lengthText;
    unsigned int paddingTopBottom;
    unsigned int paddingSides;

    Color pressBK;
    Color hoverBK;
    Color normalBK;

    Color pressFT;
    Color hoverFT;
    Color normalFT;

    Point topLeft;
    Point bottomRight;

    Button *next;
    Button *prev;
};

Button* initButton(char *name, Point topLeft, ButtonType type, ButtonStyle style);
void drawButton(Button* b);
bool cursorInArea(Button* b, int x, int y);


struct ButtonsList
{
    Point topLeft;
    Point bottomRight;

    Button *first;
    Button *last;

    unsigned int length;
    bool changes;

    bool bkChanged;
    ButtonListStyle style;
};

ButtonsList* initButtonsList(Point topLeft, char buttonsNames[][MAX_NAMES_LEN], ButtonType types[], unsigned int length, ButtonStyle style, ButtonListStyle styleBl);
void removeLastButtonFromList(ButtonsList *bl);
void clearButtonsList(ButtonsList *bl);
void deleteButtonsList(ButtonsList *bl);
void addButtonToList(ButtonsList *bl, Button *b);
bool isButtonsListEmpty(ButtonsList *bl);
void drawButtonsList(ButtonsList *bl);
bool cursorInArea(ButtonsList* bl, int x, int y);

struct MenuArea
{
    Editor *e;

    bool changes;
    Point topLeft;
    Point bottomRight;
    unsigned int separatorLength;

    ButtonsList* buttonsList;
    // Soon
};

MenuArea* initMenuArea(Point topLeft, Editor *e);
void drawArea(MenuArea *ma);
bool cursorInArea(MenuArea *ma, int x, int y);
void handleHover(MenuArea *ma, int x, int y);
void clearHover(MenuArea *ma, int x, int y);

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

struct TextArea
{
    bool changes;
    // De implementat la salvare, corespunzator pentru Windows file si unixFile (asaugare '\r' pentru windows file)
    bool unixFile;
    bool savedChanges;
    char fileName[500];

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

void updateCursorPosition(TextArea *ta, char deletedChar);
void getCursorPositionInPiecetable(TextArea *ta, Point dest);
void addCharToTextArea(TextArea *ta, char newLetter);
void removeCharFromTextArea(TextArea *ta);
void drawArea(TextArea *ta);
void drawCursorLine(TextArea *ta, bool white=false);
void moveCursor(TextArea *ta, Point dest);
void moveCursorByArrow(TextArea *ta, char a);
void openFile(TextArea *ta, char *fileName);
void saveFile(TextArea *ta, char *fileName);
void drawLines(TextArea *ta, int current_y, int end_y);

struct Editor
{
    bool running;
    bool modalOpen;
    Modal1 *m1;
    Modal2 *m2;
    MenuArea *menuArea;
    TextArea *textArea;
};

Editor* initEditor();
void drawEditor(Editor *e);
void stopEditor(Editor *e);
bool handleClick(Editor *e, int x, int y);
bool clearClick(Editor *e, int x, int y);


// This modal is to confirm actions
struct Modal1
{
    Point topLeft;
    Point bottomRight;

    char *title;
    char *description;
    Editor *e;

    ButtonsList *bl;
    void (*action)(Editor*);

    bool changes;
    bool bkChanges;
};

Modal1* initModal1(Editor *e, char *title, char *description, void (*action)(Editor*));
void deleteModal1(Modal1 *m1);
void drawModal1(Modal1 *m1);
void openModal1(Editor *e, Modal1 *m1);
void handleClick(Modal1 *m1, int x, int y);
void handleHover(Modal1 *m1, int x, int y);
void clearHover(Modal1 *m1, int x, int y);

struct CursorModal2
{
    Point position;
    time_t lastUpdate;
    InputModal2* input;

    // true for showed, false for hidden
    // this is used for blinking
    bool state;
};

CursorModal2* initCursorModal2(Point position, InputModal2 *input);
void deleteCursorModal2(CursorModal2* cursor);
void drawCursorModal2(CursorModal2 *cursor);
void changeCursor(CursorModal2* cursor);

struct InputModal2
{
    Point topLeft;
    Point bottomRight;
    Modal2 *modal;

    bool changes;
    char text[MAX_CHAR_MODAL2_INPUT+1];
    CursorModal2 *cursor;

    // true is for focused, false is for not focused
    bool state;
};

InputModal2* initInputModal2(Point topLeft, Point bottomRight, Modal2* modal);
bool cursorInArea(InputModal2* input, int x, int y);
void deleteInputModal2(InputModal2* input);
void drawInputModal2(InputModal2 *input);
void addCharToModal2Input(InputModal2* input, char x);
void deleteCharFromModal2Input(InputModal2* input);

struct Modal2
{
    Point topLeft;
    Point bottomRight;

    char *title;
    char *description;

    Editor *e;
    InputModal2 *iM;

    ButtonsList *bl;
    void (*action)(TextArea*, char*);

    bool changes;
    bool bkChanges;
};

Modal2* initModal2(Editor *e, char *title, char *description, char *buttonNameYes, char *buttonNameNo, void (*action)(TextArea*, char*));
void deleteModal2(Modal2 *m2);
void drawModal2(Modal2 *m2);
void handleClick(Modal2 *m2, int x, int y);
void handleHover(Modal2 *m2, int x, int y);
void clearHover(Modal2 *m2, int x, int y);
void clearClick(Modal2 *m2, int x, int y);

#endif // NOTEIM_EDITOR_H
