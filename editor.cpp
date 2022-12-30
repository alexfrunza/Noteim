#include <graphics.h>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>

#include "editor.h"
#include "helpers.h"

// MenuBar
#define MENU_BAR_SEPARATOR_BAR {211, 211, 211}
#define MENU_BAR_BK {0, 0, 0}

// Buttons menu bar
#define PADDING_SIDES_MENU_BAR_BUTTON 10
#define PADDING_TOP_BOTTOM_MENU_BAR_BUTTON 5

// Colors
#define HOVER_BK_MENU_BAR_BUTTON {229, 243, 255}
#define HOVER_FONT_MENU_BAR_BUTTON {0, 0, 0}
#define NORMAL_BK_MENU_BAR_BUTTON {255, 255, 255}
#define NORMAL_FONT_MENU_BAR_BUTTON {0, 0, 0}
#define PRESS_BK_MENU_BAR_BUTTON {204, 232, 255}
#define PRESS_FONT_MENU_BAR_BUTTON {0, 0, 0}

// Submenu1
#define SUBMENU1_PADDING 2
#define SUBMENU1_BK {100, 100, 100}
#define SUBMENU1_SHADOW {200, 200, 200}
#define SUBMENU1_SHADOW_OFF 7

// Buttons submenu1
#define PADDING_SIDES_SUBMENU1_BUTTON 20
#define PADDING_TOP_BOTTOM_SUBMENU1_BUTTON 5
#define LENGTH_SEPARATOR_BUTTON_BOTTOM 2

// Colors
#define HOVER_BK_SUBMENU1_BUTTON {145, 201, 247}
#define HOVER_FONT_SUBMENU1_BUTTON {0, 0, 0}
#define NORMAL_BK_SUBMENU1_BUTTON {242, 242, 242}
#define NORMAL_FONT_SUBMENU1_BUTTON {0, 0, 0}
#define PRESS_BK_SUBMENU1_BUTTON {145, 201, 247}
#define PRESS_FONT_SUBMENU1_BUTTON {0, 0, 0}

// TextArea
#define TEXTAREA_BK_NORMAL {100, 0, 100}
#define TEXTAREA_FONT_NORMAL {124, 225, 255}

// For debugging
#include <iostream>
using namespace std;
//

Button* initButton(char *name, Point topLeft, ButtonType type, ButtonStyle style)
{
    Button *b = new Button;
    b->subMenu = NULL;
    b->pressed = false;


    b->type = type;
    b->style = style;
    if(b->style == MENUBAR)
    {
        b->paddingSides = PADDING_SIDES_MENU_BAR_BUTTON;
        b->paddingTopBottom = PADDING_TOP_BOTTOM_MENU_BAR_BUTTON;
        b->hoverBK = HOVER_BK_MENU_BAR_BUTTON;
        b->hoverFT = HOVER_FONT_MENU_BAR_BUTTON;
        b->normalBK = NORMAL_BK_MENU_BAR_BUTTON;
        b->normalFT = NORMAL_FONT_MENU_BAR_BUTTON;
        b->pressBK = PRESS_BK_MENU_BAR_BUTTON;
        b->pressFT = PRESS_FONT_MENU_BAR_BUTTON;
        b->lengthText = strlen(name) * CHAR_WIDTH;
    }
    else if(b->style == SUBMENU1)
    {
        b->paddingSides = PADDING_SIDES_SUBMENU1_BUTTON;
        b->paddingTopBottom = PADDING_TOP_BOTTOM_SUBMENU1_BUTTON;
        b->hoverBK = HOVER_BK_SUBMENU1_BUTTON;
        b->hoverFT = HOVER_FONT_SUBMENU1_BUTTON;
        b->normalBK = NORMAL_BK_SUBMENU1_BUTTON;
        b->normalFT = NORMAL_FONT_SUBMENU1_BUTTON;
        b->pressBK = PRESS_BK_SUBMENU1_BUTTON;
        b->pressFT = PRESS_FONT_SUBMENU1_BUTTON;
        b->lengthText = 20 * CHAR_WIDTH;
    }

    b->next = NULL;
    b->prev = NULL;

    b->topLeft = topLeft;
    b->bottomRight = {b->topLeft.x + b->lengthText + 2*b->paddingSides, b->topLeft.y + CHAR_HEIGHT + 2*b->paddingTopBottom};

    b->text = (char*) malloc(sizeof(char) * strlen(name));
    strcpy(b->text, name);

    b->hovered = false;
    b->changes = true;

    return b;
}

void drawButton(Button* b)
{
    if(b->subMenu != NULL)
    {
        drawButtonsList(b->subMenu);
    }

    if(b->changes == false)
        return;

    if(b->pressed == true)
    {
        setfillstyle(SOLID_FILL, convertToBGIColor(b->pressBK));
        setbkcolor(convertToBGIColor(b->pressBK));
        setcolor(convertToBGIColor(b->pressFT));
    }
    else if(b->hovered == true)
    {
        setfillstyle(SOLID_FILL, convertToBGIColor(b->hoverBK));
        setbkcolor(convertToBGIColor(b->hoverBK));
        setcolor(convertToBGIColor(b->hoverFT));
    }
    else
    {
        setfillstyle(SOLID_FILL, convertToBGIColor(b->normalBK));
        setbkcolor(convertToBGIColor(b->normalBK));
        setcolor(convertToBGIColor(b->normalFT));
    }

    bar(b->topLeft.x, b->topLeft.y,  b->bottomRight.x, b->bottomRight.y);
    outtextxy(b->topLeft.x + b->paddingSides, b->topLeft.y + b->paddingTopBottom, b->text);
    b->changes = false;
}

ButtonsList* initButtonsList(Point topLeft, char buttonsNames[][MAX_NAMES_LEN], ButtonType types[], unsigned int length, ButtonStyle style, ButtonListStyle styleBl)
{
    ButtonsList* bl = new ButtonsList;
    bl->changes = true;
    bl->first = NULL;
    bl->last = NULL;
    bl->length = 0;
    bl->topLeft = topLeft;
    bl->bkChanged = true;
    bl->style = styleBl;

    if(style == MENUBAR)
    {
        for(int i=0; i<length; i++)
        {
            Button* b = initButton(buttonsNames[i], topLeft, types[i], style);
            addButtonToList(bl, b);
            topLeft.x = b->bottomRight.x;
            bl->bottomRight.x = b->bottomRight.x;
            bl->bottomRight.y = b->bottomRight.y;
        }
    }
    else if (style == SUBMENU1)
    {
        topLeft.x += SUBMENU1_PADDING;
        topLeft.y += SUBMENU1_PADDING;
        int i;
        for(i=0; i<length-1; i++)
        {
            Button* b = initButton(buttonsNames[i], topLeft, types[i], style);

            addButtonToList(bl, b);
            topLeft.y = b->bottomRight.y + LENGTH_SEPARATOR_BUTTON_BOTTOM;
            bl->bottomRight.x = b->bottomRight.x;
            bl->bottomRight.y = b->bottomRight.y;
        }
        if(length > 0)
        {
            Button* b = initButton(buttonsNames[i], topLeft, types[i], style);
            addButtonToList(bl, b);
            topLeft.y = b->bottomRight.y;
            bl->bottomRight.x = b->bottomRight.x;
            bl->bottomRight.y = b->bottomRight.y;
        }
        bl->bottomRight.x += SUBMENU1_PADDING;
        bl->bottomRight.y += SUBMENU1_PADDING;
    }

    return bl;
}

void removeLastButtonFromList(ButtonsList *bl)
{
    if(bl->length == 1)
    {
        delete bl->first;
        bl->first = NULL;
        bl->last = NULL;
        bl->length--;
        return;
    }

    if(!isButtonsListEmpty(bl))
    {
        Button *aux = bl->last;
        bl->last = bl->last->prev;
        bl->last->next = NULL;
        delete aux;
        bl->length--;
    }
}

void clearButtonsList(ButtonsList *bl)
{
    while(!isButtonsListEmpty(bl))
    {
        removeLastButtonFromList(bl);
    }
}

void deleteButtonsList(ButtonsList *bl)
{
    clearButtonsList(bl);
    delete bl;
}

void addButtonToList(ButtonsList *bl, Button *b)
{
    if(bl->length == 0)
    {
        bl->length = 1;
        bl->first = b;
        bl->last = b;
        return;
    }

    b->next = NULL;
    b->prev = bl->last;
    bl->last->next = b;
    bl->last = b;
    bl->length++;
}

bool isButtonsListEmpty(ButtonsList *bl)
{
    if(bl->length == 0) return true;
    return false;
}

void drawButtonsList(ButtonsList *bl)
{
    if(bl->bkChanged)
    {
        switch (bl->style)
        {
        case MENUBAR_BL:
            setfillstyle(SOLID_FILL, convertToBGIColor(MENU_BAR_BK));
            bar(bl->topLeft.x, bl->topLeft.y, bl->bottomRight.x, bl->bottomRight.y);
            break;
        case SUBMENU1_BL:
            setfillstyle(SOLID_FILL, convertToBGIColor(SUBMENU1_SHADOW));
            bar(bl->topLeft.x + SUBMENU1_SHADOW_OFF, bl->topLeft.y + SUBMENU1_SHADOW_OFF, bl->bottomRight.x + SUBMENU1_SHADOW_OFF, bl->bottomRight.y + SUBMENU1_SHADOW_OFF);

            setfillstyle(SOLID_FILL, convertToBGIColor(SUBMENU1_BK));
            bar(bl->topLeft.x, bl->topLeft.y, bl->bottomRight.x, bl->bottomRight.y);
            break;
        }
        bl->bkChanged = false;
    }

    for(Button *b = bl->first; b; b = b->next)
    {
        drawButton(b);
    }

    bl->changes = false;
}

bool cursorInArea(ButtonsList* bl, int x, int y)
{
    return bl->topLeft.x < x && x < bl->bottomRight.x && bl->topLeft.y < y && y < bl->bottomRight.y;
}

bool cursorInArea(Button* b, int x, int y)
{
    return b->topLeft.x < x && x < b->bottomRight.x && b->topLeft.y < y && y < b->bottomRight.y;
}

MenuArea* initMenuArea(Point topLeft)
{
    MenuArea* ma = new MenuArea;
    ma->separatorLength = 2;

    ma->topLeft = topLeft;

    char buttonsNames[][MAX_NAMES_LEN] = {"File", "Edit", "Format"};
    ButtonType types[] = {FILE_ACTIONS, EDIT, FORMAT};

    ma->buttonsList = initButtonsList({0, 0}, buttonsNames, types, 3, MENUBAR, MENUBAR_BL);
    ma->bottomRight = {MAX_WIDTH, CHAR_HEIGHT + ma->separatorLength + 2*ma->buttonsList->first->paddingTopBottom};

    ma->changes = true;
    return ma;
}

void drawArea(MenuArea *ma)
{
    if(ma->changes == false)
        return;

    setfillstyle(SOLID_FILL, convertToBGIColor(MENU_BAR_SEPARATOR_BAR));
    bar(ma->topLeft.x, ma->bottomRight.y - ma->separatorLength, ma->bottomRight.x, ma->bottomRight.y);

    drawButtonsList(ma->buttonsList);
    ma->changes = false;
}

bool cursorInArea(MenuArea *ma, int x, int y)
{
    return ma->topLeft.x < x && x < ma->bottomRight.x && ma->topLeft.y < y && y < ma->bottomRight.y;
}

void handleHover(MenuArea *ma, int x, int y)
{
    for(Button* currentButton = ma->buttonsList->first; currentButton != NULL; currentButton = currentButton->next)
    {
        if(currentButton->subMenu != NULL)
        {
            for(Button* subMenuButton = currentButton->subMenu->first; subMenuButton != NULL; subMenuButton = subMenuButton->next)
            {
                if(cursorInArea(subMenuButton, x, y) && subMenuButton->hovered == false)
                {
                    subMenuButton->hovered = true;
                    subMenuButton->changes = true;
                    ma->changes = true;
                }
            }
        }
        if(cursorInArea(currentButton, x, y) && currentButton->hovered == false)
        {
            currentButton->hovered = true;
            currentButton->changes = true;
            ma->changes = true;
        }
    }
}

void clearHover(MenuArea *ma, int x, int y)
{
    for(Button* currentButton = ma->buttonsList->first; currentButton != NULL; currentButton = currentButton->next)
    {
        if(currentButton->subMenu != NULL)
        {
            for(Button* subMenuButton = currentButton->subMenu->first; subMenuButton != NULL; subMenuButton = subMenuButton->next)
            {
                if(!cursorInArea(subMenuButton, x, y) && subMenuButton->hovered == true)
                {
                    subMenuButton->hovered = false;
                    subMenuButton->changes = true;
                    ma->changes = true;
                }
            }
        }
        if(!cursorInArea(currentButton, x, y) && currentButton->hovered == true)
        {
            currentButton->hovered = false;
            currentButton->changes = true;
            ma->changes = true;
        }
    }
}

void showFileActionsSubMenu(Button* b, MenuArea* ma)
{
    char buttonsNames[][MAX_NAMES_LEN] = {"New", "Save", "Save as..."};
    ButtonType types[] = {NEW_FILE, SAVE_FILE, SAVE_AS_FILE};

    b->subMenu = initButtonsList({b->topLeft.x, b->bottomRight.y + ma->separatorLength}, buttonsNames, types, 3, SUBMENU1, SUBMENU1_BL);
}

bool handleClick(Editor *e, int x, int y)
{
    MenuArea *ma = e->menuArea;
    for(Button* currentButton = ma->buttonsList->first; currentButton != NULL; currentButton = currentButton->next)
    {
        if(currentButton->subMenu != NULL)
        {
            for(Button* subMenuButton = currentButton->subMenu->first; subMenuButton != NULL; subMenuButton = subMenuButton->next)
            {
                if(cursorInArea(subMenuButton, x, y))
                {
                    subMenuButton->pressed = true;
                    switch (subMenuButton->type)
                    {
                    case SAVE_FILE:
                        cout<<"Am salvat fisierul\n";
                        break;
                    case NEW_FILE:
                        cout<<"Fisier nou\n";
                        break;
                    case SAVE_AS_FILE:
                        cout<<"Salveaza fisier ca...\n";
                        break;
                    }

                    deleteButtonsList(currentButton->subMenu);
                    currentButton->subMenu = NULL;

                    currentButton->pressed = false;
                    e->textArea->changes = true;
                    currentButton->changes = true;
                    subMenuButton->changes = true;
                    ma->changes = true;
                    return true;
                }
            }
        }
        if(cursorInArea(currentButton, x, y) && currentButton->pressed == false)
        {
            currentButton->pressed = true;
            switch (currentButton->type)
            {
            case FILE_ACTIONS:
                showFileActionsSubMenu(currentButton, ma);
                break;
            }

            currentButton->changes = true;
            ma->changes = true;
            return true;
        }
    }
    return false;
}

bool clearClick(Editor *e, int x, int y)
{
    MenuArea *ma = e->menuArea;
    bool pressedSubMenu = false;
    for(Button* currentButton = ma->buttonsList->first; currentButton != NULL; currentButton = currentButton->next)
    {
        if(!cursorInArea(currentButton, x, y) && currentButton->pressed == true)
        {
            switch (currentButton->type)
            {
            case FILE_ACTIONS:
                if(currentButton->subMenu != NULL && cursorInArea(currentButton->subMenu, x, y))
                {
                    pressedSubMenu = true;
                }
                if(currentButton->subMenu != NULL && !cursorInArea(currentButton->subMenu, x, y))
                {
                    deleteButtonsList(currentButton->subMenu);
                    currentButton->subMenu = NULL;
                    currentButton->pressed = false;
                    e->textArea->changes = true;
                }
                break;
            default:
                currentButton->pressed = false;
                break;
            }

            currentButton->changes = true;
            ma->changes = true;
        }
    }
    return pressedSubMenu;
}

ScrollBarsArea* initScrollBarsArea(Point topLeft, Point bottomRight)
{
}

void drawArea(ScrollBarsArea *sba)
{
}

Cursor *initCursor()
{
    Cursor* c = new Cursor;
    c->position = {0,0};
    c->positionInNode = 0;

    return c;
}

TextArea* initTextArea(Point topLeft, Point bottomRight)
{
    TextArea* ta = new TextArea;
    ta->unixFile = false;
    ta->savedChanges = true;

    ta->topLeft = topLeft;
    ta->bottomRight = bottomRight;
    ta->cursor = initCursor();
    ta->firstLine = 0;
    drawCursorLine(ta);

    ta->changes = true;
    ta->pieceTable = initPieceTable();
    Buffer *firstBuffer = initBuffer();
    addBuffer(ta->pieceTable->buffersList, firstBuffer);
    PieceTableNode *firstNode = initPieceTableNode(ta->pieceTable->buffersList->first,0,0,0);
    addPieceTableNode(ta->pieceTable->nodesList,firstNode);
    ta->cursor->pieceTableNode = ta->pieceTable->nodesList->first;
    ta->maxLines = abs(bottomRight.y - topLeft.y) / CHAR_HEIGHT;
    ta->maxCharLine = abs(bottomRight.x - topLeft.x) / CHAR_WIDTH;

    return ta;
}

TextArea* initTextArea(Point topLeft, Point bottomRight, char *fileName)
{
    TextArea* ta = new TextArea;
    ta->savedChanges = true;
    ta->unixFile = false;
    ta->changes = true;
    ta->firstLine = 0;

    ta->topLeft = topLeft;
    ta->bottomRight = bottomRight;

    ta->pieceTable = initPieceTable();

    ta->maxLines = abs(bottomRight.y - topLeft.y) / CHAR_HEIGHT;
    ta->maxCharLine = abs(bottomRight.x - topLeft.x) / CHAR_WIDTH;

    openFile(ta, fileName);
    ta->cursor = initCursor();
    drawCursorLine(ta);
    ta->cursor->pieceTableNode = ta->pieceTable->nodesList->first;
    return ta;
}

void drawCursorLine(TextArea *ta, bool white)
{
    if(white==true)
        setcolor(convertToBGIColor(TEXTAREA_BK_NORMAL));
    int x = ta->cursor->position.x*CHAR_WIDTH + ta->topLeft.x;
    int y = ta->cursor->position.y*CHAR_HEIGHT + ta->topLeft.y;
    line(x,y,x,y+CHAR_HEIGHT-1);
    setcolor(convertToBGIColor(TEXTAREA_FONT_NORMAL));
}

void getCursorPositionInPiecetable(TextArea *ta, Point dest)
{
    PieceTableNode *ptn = ta->pieceTable->nodesList->first;
    dest = {dest.x + ta->firstColumn, dest.y + ta->firstLine};

    if(ta->pieceTable->nodesList->length==1 && ptn->length==0)
    {
        ta->cursor->position = {0,0};
        ta->cursor->pieceTableNode = ptn;
        ta->cursor->positionInNode = 0;
        return;
    }

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
        while(ptn!=NULL && ptn->buffer->text[i]!='\n')
        {
            if(i==ptn->start-1)
            {
                ptn = ptn->prev;
                if(ptn!=NULL)
                    i = ptn->start+ptn->length-1;
            }
            else
                currentXInLine++;
            i--;
        }
        ta->cursor->position = {currentXInLine - ta->firstColumn, dest.y - ta->firstLine - remainingNewLines};
        ta->cursor->pieceTableNode = ta->pieceTable->nodesList->last;
        ta->cursor->positionInNode = ta->pieceTable->nodesList->last->length;
        return;
    }
    i = ptn->start;
    while(remainingNewLines!=0)
    {
        if(ptn->buffer->text[i]=='\n')
            remainingNewLines--;
        i++;
    }
    if(i==ptn->start+ptn->length)
    {
        ptn = ptn->next;
        if(ptn!=NULL)
            i = ptn->start;
    }
    while(ptn!=NULL && currentXInLine!=dest.x && (ptn->buffer->text[i]!='\n' || i==ptn->start+ptn->length))
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
    if(currentXInLine==dest.x)
    {
        ta->cursor->position = {dest.x - ta->firstColumn, dest.y - ta->firstLine};
        ta->cursor->pieceTableNode = ptn;
        ta->cursor->positionInNode = i-ptn->start;
    }
    else
    {
        ta->cursor->position = {currentXInLine - ta->firstColumn, dest.y - ta->firstLine};
        if(ptn==NULL)
        {
            ta->cursor->pieceTableNode = ta->pieceTable->nodesList->last;
            ta->cursor->positionInNode = i-ta->pieceTable->nodesList->last->start-1;
        }
        else
        {
            ta->cursor->pieceTableNode = ptn;
            ta->cursor->positionInNode = i-ptn->start;
        }
    }
}

void moveCursor(TextArea *ta, Point dest)
{
    if(ta->pieceTable->nodesList->length==1 && ta->pieceTable->nodesList->first->length==0)
        return;

    Point prevCursorPosition = ta->cursor->position;

    if(dest.x<0)
    {
        if(ta->firstColumn==0)
            return;
        ta->firstColumn--;
        ta->changes = true;
        dest.x = 0;
    }

    if(dest.y<0)
    {
        if(ta->firstLine==0)
            return;
        ta->firstLine--;
        ta->changes = true;
        dest.y = 0;
    }

    if(dest.x>=ta->maxCharLine)
    {
        ta->firstColumn++;
        ta->changes = true;
        dest.x--;
    }

    if(dest.y>=ta->maxLines)
    {
        if(dest.y>=ta->pieceTable->numberOfLines)
            return;
        ta->firstLine++;
        ta->changes = true;
        dest.y--;
    }

    drawCursorLine(ta,true);
    getCursorPositionInPiecetable(ta,dest);
    if(ta->cursor->position.x < 0)
    {
        ta->firstColumn += ta->cursor->position.x;
        ta->cursor->position.x = 0;
        ta->changes = true;
    }
    drawCursorLine(ta);
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

// WIP
void updateCursorPosition(TextArea *ta)
{
    Point dest = {0,0};
    PieceTableNode *ptn = ta->pieceTable->nodesList->first;
    int i = 0;
    while(ptn!=ta->cursor->pieceTableNode)
    {
        dest.y += ptn->numberNewLines;
        ptn = ptn->next;
    }
    while(i<ta->cursor->positionInNode)
    {
        if(ptn->buffer->text[ptn->start+i]=='\n')
            dest = {0,dest.y+1};
        else
            dest.x++;
        i++;
    }
    ta->cursor->position = dest;

    // Scroll triggers
    if(ta->cursor->position.x<0)
    {
        ta->cursor->position.x = 0;
        ta->firstColumn--;
        ta->changes = true;
    }

    if(ta->cursor->position.x>=ta->maxCharLine)
    {
        ta->firstColumn = ta->cursor->position.x - ta->maxCharLine;
        ta->cursor->position.x = ta->maxCharLine;
        ta->changes = true;
    }

    if(ta->cursor->position.y<0)
    {
        ta->cursor->position.y = 0;
        ta->firstLine--;
        ta->changes = true;
    }
    if(ta->cursor->position.y>=ta->maxLines)
    {
        ta->cursor->position.y--;
        ta->firstLine++;
        ta->changes = true;
    }
}

void addCharToTextArea(TextArea *ta, char newLetter)
{
    Cursor *c = ta->cursor;

    if(bufferIsFull(ta->pieceTable->buffersList->last))
        addBuffer(ta->pieceTable->buffersList,initBuffer());
    addElementToBuffer(newLetter, ta->pieceTable->buffersList->last);


    if(c->positionInNode==0 && c->pieceTableNode->prev!=NULL)
    {
        c->pieceTableNode = c->pieceTableNode->prev;
        c->positionInNode = c->pieceTableNode->length;
    }

    if(c->pieceTableNode->buffer==ta->pieceTable->buffersList->last && c->positionInNode==c->pieceTableNode->length
            && c->pieceTableNode->start+c->pieceTableNode->length==ta->pieceTable->buffersList->last->length-1)
    {
        c->pieceTableNode->length++;
        c->positionInNode++;
        if(newLetter=='\n')
        {
            c->position = {0,c->position.y+1};
            if(ta->firstColumn>0)
                ta->firstColumn = 0;
            c->pieceTableNode->numberNewLines++;
            ta->pieceTable->numberOfLines++;
        }
        else
            c->position.x++;
        return;
    }

    PieceTableNode *newNode = initPieceTableNode(ta->pieceTable->buffersList->last,ta->pieceTable->buffersList->last->length-1,1,newLetter=='\n'?1:0);

    if(c->positionInNode==c->pieceTableNode->length)
    {
        if(c->pieceTableNode->next!=NULL)
        {
            newNode->next = c->pieceTableNode->next;
            c->pieceTableNode->next->prev = newNode;
        }
        else
            ta->pieceTable->nodesList->last = newNode;
        newNode->prev = c->pieceTableNode;
        c->pieceTableNode->next = newNode;
        ta->pieceTable->nodesList->length++;

        if(newLetter=='\n')
        {
            if(ta->firstColumn>0)
                ta->firstColumn = 0;
            c->position = {0,c->position.y+1};
            ta->pieceTable->numberOfLines++;
        }
        else
            c->position.x++;
        c->pieceTableNode = newNode;
        c->positionInNode = 1;
        return;
    }

    if(c->positionInNode==0)
    {
        if(c->pieceTableNode->prev!=NULL)
        {
            newNode->prev = c->pieceTableNode->prev;
            c->pieceTableNode->prev->next = newNode;
        }
        else
            ta->pieceTable->nodesList->first = newNode;
        newNode->next = c->pieceTableNode;
        c->pieceTableNode->prev = newNode;
        ta->pieceTable->nodesList->length++;

        if(newLetter=='\n')
        {
            if(ta->firstColumn>0)
                ta->firstColumn = 0;
            c->position = {0,c->position.y+1};
            ta->pieceTable->numberOfLines++;
        }
        else
            c->position.x++;
        c->pieceTableNode = newNode;
        c->positionInNode = 1;
        return;
    }

    {
        PieceTableNode *rightSide = initPieceTableNode(c->pieceTableNode->buffer,c->pieceTableNode->start+c->positionInNode,c->pieceTableNode->length-c->positionInNode,0);
        for(int i=rightSide->start+rightSide->length-1; i>=(int)rightSide->start; i--)
            if(rightSide->buffer->text[i]=='\n')
                rightSide->numberNewLines++;

        c->pieceTableNode->numberNewLines -= rightSide->numberNewLines;
        c->pieceTableNode->length = c->positionInNode;


        if(c->pieceTableNode->next!=NULL)
        {
            c->pieceTableNode->next->prev = rightSide;
            rightSide->next = c->pieceTableNode->next;
        }
        else
            ta->pieceTable->nodesList->last = rightSide;
        rightSide->prev = newNode;
        newNode->next = rightSide;
        c->pieceTableNode->next = newNode;
        newNode->prev = c->pieceTableNode;

        if(newLetter=='\n')
        {
            if(ta->firstColumn>0)
                ta->firstColumn = 0;
            c->position = {0,c->position.y+1};
            ta->pieceTable->numberOfLines++;
        }
        else
            c->position.x++;
        c->pieceTableNode = newNode;
        c->positionInNode = 1;
        ta->pieceTable->nodesList->length+=2;

        return;
    }
}

// Needs scroll handling method.
void removeCharFromTextArea(TextArea *ta)
{
    int i;
    char deletedChar;
    Cursor *c = ta->cursor;
    PieceTableNode *ptn;

    if(c->positionInNode==0 && (c->pieceTableNode->prev==NULL || c->pieceTableNode->prev->length==0))
        return;

    if(c->positionInNode==0)
    {
        c->pieceTableNode = c->pieceTableNode->prev;
        c->positionInNode = c->pieceTableNode->length;
    }

    c->positionInNode--;
    deletedChar = c->pieceTableNode->buffer->text[c->pieceTableNode->start+c->positionInNode];
    if(deletedChar=='\n')
        ta->pieceTable->numberOfLines--;

    if(c->positionInNode==c->pieceTableNode->length-1)
    {
        c->pieceTableNode->length--;
        updateCursorPosition(ta);
        if(c->pieceTableNode->length==0 && c->pieceTableNode->prev!=NULL)
        {
            ta->pieceTable->nodesList->length--;
            ptn = c->pieceTableNode;
            if(c->pieceTableNode==ta->pieceTable->nodesList->last)
            {
                ta->pieceTable->nodesList->last = c->pieceTableNode->prev;
                c->pieceTableNode->prev->next = NULL;
            }
            else
            {
                c->pieceTableNode->prev->next = c->pieceTableNode->next;
                c->pieceTableNode->next->prev = c->pieceTableNode->prev;
            }
            c->pieceTableNode = c->pieceTableNode->prev;
            c->positionInNode = c->pieceTableNode->length;
            delete ptn;
        }
        return;
    }

    if(c->positionInNode==0)
    {
        c->pieceTableNode->start++;
        c->pieceTableNode->length--;
        updateCursorPosition(ta);
        return;
    }

    {
        PieceTableNode *rightSide = initPieceTableNode(c->pieceTableNode->buffer,c->pieceTableNode->start+c->positionInNode+1,c->pieceTableNode->length-c->positionInNode+1,0);
        for(i=c->positionInNode+1; i<c->pieceTableNode->length; i++)
            if(c->pieceTableNode->buffer->text[c->pieceTableNode->start+i]=='\n')
                rightSide->numberNewLines++;
        c->pieceTableNode->length = c->positionInNode;
        c->pieceTableNode->numberNewLines -= rightSide->numberNewLines;
        if(c->pieceTableNode == ta->pieceTable->nodesList->last)
        {
            ta->pieceTable->nodesList->last = rightSide;
            rightSide->next = NULL;
        }
        else
        {
            rightSide->next = c->pieceTableNode->next;
            c->pieceTableNode->next->prev = rightSide;
        }
        c->pieceTableNode->next = rightSide;
        rightSide->prev = c->pieceTableNode;
        ta->pieceTable->nodesList->length++;
        updateCursorPosition(ta);
        return;
    }
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

    topLeft= {0, 0};
    e->menuArea = initMenuArea(topLeft);

    topLeft= {0,0};
    bottomRight = {MAX_WIDTH,MAX_HEIGHT};

    //
    // e->scrollBarsArea = initScrollBarsArea(topLeft, bottomRight);
    // De mutat in initTextArea

    topLeft= {0, e->menuArea->bottomRight.y};
    bottomRight = {MAX_WIDTH,MAX_HEIGHT};

    // !!!!!!!!!!!!!!!!!!!!!!!!
    // Citire din fisier
    //cout<<"TOP LEFT: "<<topLeft.x<<" "<<topLeft.y<<'\n';
    //cout<<"RIGHT BOTTOM: "<<bottomRight.x<<" "<<bottomRight.y<<'\n';


    e->textArea = initTextArea(topLeft, bottomRight, "textText.txt");
    //e->textArea = initTextArea(topLeft, bottomRight);

    return e;
}

void drawCharsInGui(Buffer* b, int x, int y, long index, long endOfDisplayedLine)
{
    char aux = b->text[endOfDisplayedLine];
    b->text[endOfDisplayedLine] = '\0';
    outtextxy(x, y, b->text + index);
    b->text[endOfDisplayedLine] = aux;
}

void showALine(int y, TextArea* ta, PieceTableNode* ptn, long indexOfLine)
{
    long numberOfCharsFromNode;
    long spaceRemainedOnScreen = ta->maxCharLine - 1;
    long current_x = ta->topLeft.x;
    long endOfDisplayedLine;
    long skippedChars = ta->firstColumn;
    bool lineEnded = false;
    bool skippedNode;

    setbkcolor(convertToBGIColor(TEXTAREA_BK_NORMAL));
    setcolor(convertToBGIColor(TEXTAREA_FONT_NORMAL));

    while(spaceRemainedOnScreen > 0 && !lineEnded && ptn != NULL)
    {
        numberOfCharsFromNode = ptn->length - (indexOfLine - ptn->start);
        endOfDisplayedLine = indexOfLine + numberOfCharsFromNode;
        skippedNode = false;

        // For horizontal scroll
        if(skippedChars > 0)
        {
            char aux = ptn->buffer->text[endOfDisplayedLine];
            ptn->buffer->text[endOfDisplayedLine] = '\0';
            //cout<<"END from skipped: "<<endOfDisplayedLine<<'\n';
            char *newLineInNode = strchr(ptn->buffer->text + indexOfLine, '\n');
            ptn->buffer->text[endOfDisplayedLine] = aux;

            // cout<<"START: "<<indexOfLine<<" "<<endOfDisplayedLine<<'\n';
            if(newLineInNode)
            {
                //cout<<"SKIPPED: "<<skippedChars<<'\n';
                if((void*)newLineInNode <= (void*)ptn->buffer->text + indexOfLine + skippedChars) break;

                indexOfLine += skippedChars;
                numberOfCharsFromNode -= endOfDisplayedLine - (newLineInNode - ptn->buffer->text + 1);
                endOfDisplayedLine = newLineInNode - ptn->buffer->text + 1;
            }
            else
            {
                if(numberOfCharsFromNode <= skippedChars)
                {
                    skippedChars = skippedChars - numberOfCharsFromNode;
                    skippedNode = true;
                }
                else
                {
                    numberOfCharsFromNode -= skippedChars;
                    indexOfLine += skippedChars;
                    skippedChars = 0;
                }
            }
            // //cout<<"start: "<<indexOfLine<<" end: "<<endOfDisplayedLine<<'\n';
            // cout<<"numberOfCharsFromNode: "<<numberOfCharsFromNode<<'\n';
            //cout<<"SKIPPEd: "<<skippedChars<<'\n';
        }
        // end

        if(numberOfCharsFromNode <= spaceRemainedOnScreen && !skippedNode)
        {
            endOfDisplayedLine = indexOfLine + numberOfCharsFromNode;

            char aux = ptn->buffer->text[endOfDisplayedLine];
            ptn->buffer->text[endOfDisplayedLine] = '\0';
            //cout<<"END: "<<endOfDisplayedLine<<'\n';
            char *newLineInNode = strchr(ptn->buffer->text + indexOfLine, '\n');
            //cout<<"POINTER NEW LINE: "<<(void*)newLineInNode<<'\n';
            ptn->buffer->text[endOfDisplayedLine] = aux;

            if(newLineInNode)
            {
                numberOfCharsFromNode -= endOfDisplayedLine - (newLineInNode - ptn->buffer->text + 1);
                endOfDisplayedLine = newLineInNode - ptn->buffer->text + 1;
                lineEnded = true;
                //cout<<"INDEXXXX: "<<indexOfLine<<" "<<endOfDisplayedLine<<endl;
            }

            //cout<<"DE la caracter mai mic: "<<indexOfLine<<" "<<endOfDisplayedLine<<endl;
            spaceRemainedOnScreen -= numberOfCharsFromNode;
            drawCharsInGui(ptn->buffer, current_x, y, indexOfLine, endOfDisplayedLine);
            current_x += numberOfCharsFromNode * CHAR_WIDTH;
        }
        else if(!skippedNode)
        {
            endOfDisplayedLine = indexOfLine + spaceRemainedOnScreen;

            char aux = ptn->buffer->text[endOfDisplayedLine];
            ptn->buffer->text[endOfDisplayedLine] = '\0';
            char *newLineInNode = strchr(ptn->buffer->text + indexOfLine, '\n');
            ptn->buffer->text[endOfDisplayedLine] = aux;

            if(newLineInNode)
            {
                endOfDisplayedLine = newLineInNode - ptn->buffer->text + 1;
                lineEnded = true;
            }

            //cout<<"DE la caracter mai mare: "<<indexOfLine<<" "<<endOfDisplayedLine<<endl;
            drawCharsInGui(ptn->buffer, current_x, y, indexOfLine, endOfDisplayedLine);
            lineEnded = true;
        }

        ptn = ptn->next;
        if(ptn != NULL) indexOfLine = ptn->start;
    }
}

void drawLines(TextArea *ta, int current_y, int end_y)
{
    setfillstyle(1, convertToBGIColor(TEXTAREA_BK_NORMAL));
    bar(ta->topLeft.x, current_y, ta->bottomRight.x, end_y);

    long showedLines = (current_y - ta->topLeft.y) / CHAR_HEIGHT;
    long currentLine = ta->firstLine + showedLines;
    long mustShowLines = (end_y - ta->topLeft.y) / CHAR_HEIGHT;

    while(showedLines < mustShowLines)
    {
        PieceTableNode* lineNode;
        long indexOfLine;

        getWhereLineStarts(ta->pieceTable, currentLine, lineNode, indexOfLine);
        if(!lineNode)
        {
            break;
        }

        showALine(current_y, ta, lineNode, indexOfLine);

        current_y += CHAR_HEIGHT;
        currentLine++;
        showedLines++;
    }
}

void drawArea(TextArea *ta)
{
    if(ta->changes==false)
        return;

    int current_y=ta->topLeft.y;
    long showedLines = 0;
    long currentLine = ta->firstLine;

    drawLines(ta, current_y, ta->bottomRight.y);

    drawCursorLine(ta);
}

void openFile(TextArea *ta, char *fileName)
{
    FILE *file = fopen(fileName, "rb");

    if(file == NULL)
    {
        fclose(file);
        printf("Eroare la citirea fisierului!\n");
        return;
    }

    emptyPieceTable(ta->pieceTable);

    bool unixFile = false;
    unsigned int readSize;
    char lastAddedChar = '\0';
    int numberOfSpaces = 0;
    bool ok = false;

    do
    {
        char last_x;
        if(fread(&last_x, sizeof(char), 1, file) == 0)
        {
            last_x = '\0';
            readSize = 0;
        }

        Buffer *newBuffer;
        if(numberOfSpaces > 0 || last_x != '\0')
        {
            newBuffer = initBuffer();
            addBuffer(ta->pieceTable->buffersList, newBuffer);
            newBuffer->length = 0;
        }
        for(int i=0; i<numberOfSpaces; i++)
        {
            newBuffer->text[newBuffer->length] = ' ';
            newBuffer->length++;
            lastAddedChar = ' ';
        }
        if(numberOfSpaces > 0)
        {
            numberOfSpaces = 0;
            ok = true;
        }

        unsigned int numberNewLines = 0;
        char x;

        if(last_x == '\n')
        {
            if(lastAddedChar == '\r')
            {
                ta->pieceTable->numberOfLines += 1;
                ta->pieceTable->buffersList->last->text[ta->pieceTable->buffersList->last->length-1] = '\n';
                ta->pieceTable->nodesList->last->numberNewLines += 1;
            }
            else
            {
                numberNewLines++;
                unixFile = true;
                newBuffer->length++;
            }
        }
        else if (last_x == '\t')
        {
            for(int i=0; i<4; i++)
            {
                newBuffer->text[newBuffer->length] = ' ';
                newBuffer->length++;
            }
            last_x == ' ';
        }
        else if (last_x != '\0')
        {
            newBuffer->text[newBuffer->length] = last_x;
            newBuffer->length++;
        }

        while((newBuffer->length < MAX_LENGTH_BUFFER) && fread(&x, sizeof(char), 1, file))
        {
            newBuffer->text[newBuffer->length] = x;
            if(x == '\n') numberNewLines++;
            if(x == '\n' && last_x != '\r') unixFile = true;
            if(x == '\n' && last_x == '\r')
            {
                newBuffer->length--;
                newBuffer->text[newBuffer->length] = x;
            }
            if(x == '\t')
            {
                if(newBuffer->length + 4 > MAX_LENGTH_BUFFER)
                {
                    numberOfSpaces = newBuffer->length + 4 - MAX_LENGTH_BUFFER;
                    for(int i=newBuffer->length; i<=MAX_LENGTH_BUFFER; i++)
                    {
                        newBuffer->text[newBuffer->length] = ' ';
                    }
                    newBuffer->length = MAX_LENGTH_BUFFER;
                }
                else
                {
                    for(int i=0; i<4; i++)
                    {
                        newBuffer->text[newBuffer->length] = ' ';
                        newBuffer->length++;
                    }
                }
                last_x = ' ';
            }
            else
            {
                newBuffer->length++;
                last_x = x;
            }
        }
        if(last_x != '\0' || ok)
        {
            PieceTableNode *newNode = initPieceTableNode(newBuffer, 0, newBuffer->length, numberNewLines);
            addPieceTableNode(ta->pieceTable->nodesList, newNode);
            ta->pieceTable->numberOfLines += numberNewLines;

            //cout<<"lungimE buffer: "<<newBuffer->length<<"CARACTER: *"<<(int)newBuffer->text[0]<<"*"<<endl;
            lastAddedChar = newBuffer->text[newBuffer->length-1];
            readSize = newBuffer->length;

            /*if(newBuffer->length == 1 && newBuffer->text[0] == '\0') {
                emptyPieceTable(ta->pieceTable);
            }*/
            ok = false;
        }
    }
    while(readSize == MAX_LENGTH_BUFFER);

    if(unixFile) ta->unixFile = true;
    Buffer *newBuffer = initBuffer();
    addBuffer(ta->pieceTable->buffersList, newBuffer);

    fclose(file);
}

void saveFile(TextArea *ta, char *fileName)
{
    FILE *file = fopen(fileName, "wb");

    if(file == NULL)
    {
        fclose(file);
        printf("Eroare la scrierea fisierului!\n");
        return;
    }

    for(PieceTableNode *currentNode = ta->pieceTable->nodesList->first; currentNode != NULL; currentNode = currentNode->next)
    {
        if(currentNode->numberNewLines == 0)
        {
            fwrite(currentNode->buffer->text + currentNode->start, sizeof(char), currentNode->length, file);
        }
        else
        {
            if(ta->unixFile == false)
            {
                fwrite(currentNode->buffer->text + currentNode->start, sizeof(char), currentNode->length, file);
            }
            else
            {
                for(unsigned int i = 0; i < currentNode->length; i++)
                {
                    if(*(currentNode->buffer->text + currentNode->start + i) == '\n')
                    {
                        char newLineWin[] = {'\r', '\n'};
                        fwrite(newLineWin, sizeof(char), 2, file);
                    }
                    else
                    {
                        fwrite(currentNode->buffer->text + currentNode->start + i, sizeof(char), 1, file);
                    }
                }
            }
        }
    }
    fclose(file);
}

void drawEditor(Editor *e)
{
    drawArea(e->textArea);
    drawArea(e->menuArea);
    //drawArea(e->scrollBarsArea);
    e->textArea->changes = false;
}

void stopEditor(Editor *e)
{
    e->running = false;
    closegraph();
    // TODO: Delete data from memory
}
