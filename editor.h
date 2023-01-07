#include <graphics.h>
#include "piecetable.h"
#include "color.h"
#include <ctime>

#ifndef NOTEIM_EDITOR_H
#define NOTEIM_EDITOR_H

#define MAX_WIDTH getmaxwidth()
#define MAX_HEIGHT getmaxheight()
#define MAX_NAMES_LEN 50
#define MAX_CHAR_MODAL2_INPUT 128

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
struct TextAreaNodeTreeList;
struct TextAreaNodeTree;


enum ButtonType
{
    FILE_ACTIONS,
    MOVE,
    GO_TO_LINE,
    GO_TO_COLUMN,
    GO_TO_END_LINE,
    GO_TO_START_LINE,
    MOVE_TA_UP,
    MOVE_TA_DOWN,
    MOVE_TA_RIGHT,
    MOVE_TA_LEFT,
    SWITCH_ORIENTATION_V,
    SWITCH_ORIENTATION_H,
    OPTIONS,
    SHOW_LINES,
    HIDE_LINES,
    CLOSE_WINDOW,
    STOP_EDITOR,
    NEW_WINDOW,
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

    bool active;

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
    bool bkChanges;
    Point topLeft;
    Point bottomRight;
    unsigned int separatorLength;

    bool fileStateChanged;

    ButtonsList* buttonsList;
};

MenuArea* initMenuArea(Point topLeft, Editor *e);
void showFileActionsSubMenu(Button* b, MenuArea* ma);
void showMoveSubMenu(Button* b, MenuArea* ma);
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
    unsigned int lastBlip;
    bool visibleState;

    PieceTableNode* pieceTableNode;
    unsigned int positionInNode;
};

Cursor* initCursor();

struct TextArea
{
    Editor* e;
    bool changes;
    bool unixFile;
    bool savedChanges;
    char fileName[500];

    unsigned int maxLines;
    unsigned short int maxCharLine;

    Point topLeft;
    Point bottomRight;

    Point topLeftNumbers;
    Point bottomRightNumbers;
    bool numbersDisplayed;


    Point topLeftWindow;
    Point bottomRightWindow;

    Cursor *cursor;
    unsigned int firstLine;
    unsigned int firstColumn;

    PieceTable *pieceTable;
    //ScrollBarsArea *scrollBarsArea;
    //Memorez fila in care lucrez curent, daca e deschisa, sa stiu sa salvez tot in ea.

    bool bkChanges;

    TextAreaNodeTree *node;
};

TextArea* initTextArea(Editor *e, Point topLeft, Point bottomRight);
TextArea* initTextArea(Editor *e, Point topLeft, Point bottomRight, char *fileName);

void handleScroll(TextArea *ta);
void updateCursorPosition(TextArea *ta);
void getCursorPositionInPiecetable(TextArea *ta, Point dest);

void addCharToTextArea(TextArea *ta, char newLetter);
void removeCharFromTextArea(TextArea *ta);
void drawArea(TextArea *ta);
void drawCursorLine(TextArea *ta, bool background=false);
void blipCursor(TextArea *ta);
void moveCursor(TextArea *ta, Point dest);
void moveCursorByArrow(TextArea *ta, char a);
bool openFile(TextArea *ta, char *fileName);
bool saveFile(TextArea *ta, char *fileName);
void drawLines(TextArea *ta, int current_y, int end_y);
void drawLinesNumber(TextArea *ta);
void drawBorderTextArea(TextArea *ta);
void changeFocusedTextArea(TextAreaNodeTree *root, int x, int y);

void deleteTextArea(TextArea *ta);
bool cursorInArea(TextArea *ta, int x, int y);

struct Clipboard
{
    Cursor *start;
    Cursor *finish;

    PieceTable *pieceTable;
};

Clipboard* initClipboard(); // Done
void emptyClipboard(Clipboard *c); // Done
void selectAll(Clipboard *c, TextArea *ta); // Done?
void copyToClipboard(Clipboard *c, TextArea *ta); // Done?
void deleteSelection(Clipboard *c, TextArea *ta); // Done?
void cutSelection(Clipboard *c, TextArea *ta);
void pasteFromClipboard(Clipboard *c, TextArea *ta);
void replaceSelection(Clipboard *c, TextArea *ta);

struct Editor
{
    bool running;
    bool modalOpen;
    Modal1 *m1;
    Modal2 *m2;
    Clipboard *clipboard;
    MenuArea *menuArea;
    TextArea *textArea;
    TextAreaNodeTree *root;
    Point topLeftTextArea;
    Point bottomRightTextArea;
};

Editor* initEditor();
void drawEditor(Editor *e);
void stopEditor(Editor *e);
bool handleClick(Editor *e, int x, int y);
bool clearClick(Editor *e, int x, int y);
bool cursorInTextSpace(Editor *e, int x, int y);
void handleClickChangeTextArea(Editor *e, int x, int y);

// This modal is to confirm actions
struct Modal1
{
    Point topLeft;
    Point bottomRight;

    char *title;
    char *description;
    Editor *e;

    ButtonsList *bl;
    ButtonType buttonType;

    bool changes;
    bool bkChanges;
};

Modal1* initModal1(Editor *e, char *title, char *description, ButtonType buttonType);
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

    char *errorMessage;
    bool error;
    bool errorMessageChanges;

    Editor *e;
    InputModal2 *iM;

    ButtonsList *bl;
    ButtonType buttonType;

    bool changes;
    bool bkChanges;
};

Modal2* initModal2(Editor *e, char *title, char *description, char *buttonNameYes, char *buttonNameNo, ButtonType buttonType);
void setErrorMessageModal2(Modal2 *m2, char *message);
void deleteModal2(Modal2 *m2);
void drawModal2(Modal2 *m2);
void handleClick(Modal2 *m2, int x, int y);
void handleHover(Modal2 *m2, int x, int y);
void clearHover(Modal2 *m2, int x, int y);
void clearClick(Modal2 *m2, int x, int y);

enum TextAreaNodeTreeType
{
    ORIENTATION,
    LEAF_NODE,
};

enum Orientation
{
    HORIZONTAL,
    VERTICAL
};

enum DirectionTextArea
{
    D_UP,
    D_DOWN,
    D_RIGHT,
    D_LEFT
};

struct TextAreaNodeTree
{
    bool changes;
    Editor *e;
    Point topLeft;
    Point bottomRight;

    TextAreaNodeTreeType type;

    TextArea *ta;
    Orientation orientation;
    TextAreaNodeTreeList *tantl;
    TextAreaNodeTreeList *parentList;

    TextAreaNodeTree *next;
    TextAreaNodeTree *prev;
};

void calculateDimensionsForTextAreas(TextAreaNodeTree *root);
TextAreaNodeTree* initTextAreaNodeTree(Editor *e, Orientation orientation);
TextAreaNodeTree* initTextAreaNodeTree(Editor *e, TextArea *ta);
void drawTextAreaTree(TextAreaNodeTree *root);
void moveTextArea(TextAreaNodeTree *tant, TextArea *ta, DirectionTextArea direction);
void switchOrientation(Editor *e, Orientation orientation);
// TODO
void deleteTANT(TextAreaNodeTree *tant);

struct TextAreaNodeTreeList
{
    Editor *e;
    TextAreaNodeTree *first;
    TextAreaNodeTree *last;
    TextAreaNodeTree *parent;

    unsigned int length;
};

TextAreaNodeTreeList* initTextAreaNodeTreeList(Editor *e);
int getNodePositionInTANTL(TextAreaNodeTreeList *tantl, TextAreaNodeTree *node);
void addNodeToTANTL(TextAreaNodeTreeList *tantl, int position, TextAreaNodeTree *node);
// TODO
void deleteTANTL(TextAreaNodeTreeList *tantl);

#endif // NOTEIM_EDITOR_H
