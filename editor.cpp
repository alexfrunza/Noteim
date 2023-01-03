#include <graphics.h>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <ctime>

#include "editor.h"
#include "helpers.h"

// MenuBar
#define MENU_BAR_SEPARATOR_BAR {211, 211, 211}
#define MENU_BAR_BK {255, 255, 255}
#define MENU_BAR_FONT {0, 0, 0}

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
#define SUBMENU1_CHARS_BUTTON 20

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
#define TEXTAREA_NUMBERS_COLOR {0, 0, 0}

// Modal1 - confirmation modal
#define MODAL1_BK_NORMAL {150, 150, 150}
#define MODAL1_FONT_NORMAL {0, 0, 0}
#define MODAL1_SHADOW {170, 170, 170}
#define MODAL1_SHADOW_OFF 15
#define MODAL1_PADDING 30
#define MODAL1_HEIGHT 200
#define MODAL1_WIDTH 600
#define MODAL1_CHARS_BUTTON 10

// Buttons modal1
#define PADDING_SIDES_MODAL1_BTN 20
#define PADDING_TOP_BOTTOM_MODAL1_BTN 10

#define HOVER_BK_MODAL1_YES_BUTTON {41, 204, 82}
#define HOVER_FONT_MODAL1_YES_BUTTON {0, 0, 0}
#define NORMAL_BK_MODAL1_YES_BUTTON {52, 255, 104}
#define NORMAL_FONT_MODAL1_YES_BUTTON {0, 0, 0}
#define PRESS_BK_MODAL1_YES_BUTTON {41, 204, 82}
#define PRESS_FONT_MODAL1_YES_BUTTON {0, 0, 0}

#define HOVER_BK_MODAL1_NO_BUTTON {217, 61, 92}
#define HOVER_FONT_MODAL1_NO_BUTTON {0, 0, 0}
#define NORMAL_BK_MODAL1_NO_BUTTON {255, 71, 109}
#define NORMAL_FONT_MODAL1_NO_BUTTON {0, 0, 0}
#define PRESS_BK_MODAL1_NO_BUTTON {217, 61, 92}
#define PRESS_FONT_MODAL1_NO_BUTTON {0, 0, 0}

// Modal2 - input modal
#define MODAL2_BK_NORMAL {150, 150, 150}
#define MODAL2_FONT_NORMAL {0, 0, 0}
#define MODAL2_SHADOW {170, 170, 170}
#define MODAL2_SHADOW_OFF 15
#define MODAL2_PADDING 30
#define MODAL2_HEIGHT 300
#define MODAL2_WIDTH 800
#define MODAL2_CHARS_BUTTON 10
#define MODAL2_ERROR_MSG_COLOR {255, 45, 52}

// Input modal2
#define INPUT_MODAL2_MARGIN_COLOR {75, 75, 75}
#define INPUT_MODAL2_MARGIN_FOCUSED {0, 0, 0}
#define INPUT_MODAL2_MARGIN_SIZE 3
#define INPUT_MODAL2_PADDING 10
#define INPUT_MODAL2_CURSOR_COLOR {0, 0, 0}
#define INPUT_MODAL2_NORMAL_BK {175, 175, 175}
#define INPUT_MODAL2_NORMAL_FONT {25, 25, 25}
#define INPUT_MODAL2_FOCUSED_BK {255, 255, 255}
#define INPUT_MODAL2_FOCUSED_FONT {0, 0, 0}

// Buttons modal2
#define PADDING_SIDES_MODAL2_BTN 20
#define PADDING_TOP_BOTTOM_MODAL2_BTN 10

#define HOVER_BK_MODAL2_YES_BUTTON {41, 204, 82}
#define HOVER_FONT_MODAL2_YES_BUTTON {0, 0, 0}
#define NORMAL_BK_MODAL2_YES_BUTTON {52, 255, 104}
#define NORMAL_FONT_MODAL2_YES_BUTTON {0, 0, 0}
#define PRESS_BK_MODAL2_YES_BUTTON {41, 204, 82}
#define PRESS_FONT_MODAL2_YES_BUTTON {0, 0, 0}

#define HOVER_BK_MODAL2_NO_BUTTON {217, 61, 92}
#define HOVER_FONT_MODAL2_NO_BUTTON {0, 0, 0}
#define NORMAL_BK_MODAL2_NO_BUTTON {255, 71, 109}
#define NORMAL_FONT_MODAL2_NO_BUTTON {0, 0, 0}
#define PRESS_BK_MODAL2_NO_BUTTON {217, 61, 92}
#define PRESS_FONT_MODAL2_NO_BUTTON {0, 0, 0}

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
    switch (b->style)
    {
    case MENUBAR:
        b->paddingSides = PADDING_SIDES_MENU_BAR_BUTTON;
        b->paddingTopBottom = PADDING_TOP_BOTTOM_MENU_BAR_BUTTON;
        b->hoverBK = HOVER_BK_MENU_BAR_BUTTON;
        b->hoverFT = HOVER_FONT_MENU_BAR_BUTTON;
        b->normalBK = NORMAL_BK_MENU_BAR_BUTTON;
        b->normalFT = NORMAL_FONT_MENU_BAR_BUTTON;
        b->pressBK = PRESS_BK_MENU_BAR_BUTTON;
        b->pressFT = PRESS_FONT_MENU_BAR_BUTTON;
        b->lengthText = strlen(name) * CHAR_WIDTH;
        break;
    case SUBMENU1:
        b->paddingSides = PADDING_SIDES_SUBMENU1_BUTTON;
        b->paddingTopBottom = PADDING_TOP_BOTTOM_SUBMENU1_BUTTON;
        b->hoverBK = HOVER_BK_SUBMENU1_BUTTON;
        b->hoverFT = HOVER_FONT_SUBMENU1_BUTTON;
        b->normalBK = NORMAL_BK_SUBMENU1_BUTTON;
        b->normalFT = NORMAL_FONT_SUBMENU1_BUTTON;
        b->pressBK = PRESS_BK_SUBMENU1_BUTTON;
        b->pressFT = PRESS_FONT_SUBMENU1_BUTTON;
        b->lengthText = SUBMENU1_CHARS_BUTTON * CHAR_WIDTH;
        break;
    case MODAL1_CONFIRM_STYLE:
        b->paddingSides = PADDING_SIDES_MODAL1_BTN;
        b->paddingTopBottom = PADDING_TOP_BOTTOM_MODAL1_BTN;

        b->hoverBK = HOVER_BK_MODAL1_YES_BUTTON;
        b->hoverFT = HOVER_FONT_MODAL1_YES_BUTTON;
        b->normalBK = NORMAL_BK_MODAL1_YES_BUTTON;
        b->normalFT = NORMAL_FONT_MODAL1_YES_BUTTON;
        b->pressBK = PRESS_BK_MODAL1_YES_BUTTON;
        b->pressFT = PRESS_FONT_MODAL1_YES_BUTTON;


        b->lengthText = MODAL1_CHARS_BUTTON * CHAR_WIDTH;
        break;
    case MODAL1_CANCEL_STYLE:
        b->paddingSides = PADDING_SIDES_MODAL1_BTN;
        b->paddingTopBottom = PADDING_TOP_BOTTOM_MODAL1_BTN;

        b->hoverBK = HOVER_BK_MODAL1_NO_BUTTON;
        b->hoverFT = HOVER_FONT_MODAL1_NO_BUTTON;
        b->normalBK = NORMAL_BK_MODAL1_NO_BUTTON;
        b->normalFT = NORMAL_FONT_MODAL1_NO_BUTTON;
        b->pressBK = PRESS_BK_MODAL1_NO_BUTTON;
        b->pressFT = PRESS_FONT_MODAL1_NO_BUTTON;

        b->lengthText = MODAL1_CHARS_BUTTON * CHAR_WIDTH;
        break;
    case MODAL2_CONFIRM_STYLE:
        b->paddingSides = PADDING_SIDES_MODAL2_BTN;
        b->paddingTopBottom = PADDING_TOP_BOTTOM_MODAL2_BTN;

        b->hoverBK = HOVER_BK_MODAL2_YES_BUTTON;
        b->hoverFT = HOVER_FONT_MODAL2_YES_BUTTON;
        b->normalBK = NORMAL_BK_MODAL2_YES_BUTTON;
        b->normalFT = NORMAL_FONT_MODAL2_YES_BUTTON;
        b->pressBK = PRESS_BK_MODAL2_YES_BUTTON;
        b->pressFT = PRESS_FONT_MODAL2_YES_BUTTON;


        b->lengthText = max(int(strlen(name)), MODAL2_CHARS_BUTTON) * CHAR_WIDTH;
        break;
    case MODAL2_CANCEL_STYLE:
        b->paddingSides = PADDING_SIDES_MODAL2_BTN;
        b->paddingTopBottom = PADDING_TOP_BOTTOM_MODAL2_BTN;

        b->hoverBK = HOVER_BK_MODAL2_NO_BUTTON;
        b->hoverFT = HOVER_FONT_MODAL2_NO_BUTTON;
        b->normalBK = NORMAL_BK_MODAL2_NO_BUTTON;
        b->normalFT = NORMAL_FONT_MODAL2_NO_BUTTON;
        b->pressBK = PRESS_BK_MODAL2_NO_BUTTON;
        b->pressFT = PRESS_FONT_MODAL2_NO_BUTTON;

        b->lengthText = MODAL2_CHARS_BUTTON * CHAR_WIDTH;
        break;
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

    int x;
    switch (b->style)
    {
    // Center text in button for modal buttons
    case MODAL1_CONFIRM_STYLE:
    case MODAL1_CANCEL_STYLE:
    case MODAL2_CONFIRM_STYLE:
    case MODAL2_CANCEL_STYLE:
        x = (b->topLeft.x + b->bottomRight.x - strlen(b->text)*CHAR_WIDTH) / 2;
        outtextxy(x, b->topLeft.y + b->paddingTopBottom, b->text);
        break;
    default:
        outtextxy(b->topLeft.x + b->paddingSides, b->topLeft.y + b->paddingTopBottom, b->text);
        break;
    }
    b->changes = false;
}

ButtonsList* initButtonsList(Point topLeft, char buttonsNames[][MAX_NAMES_LEN], ButtonType types[], unsigned int length, ButtonStyle styles[], ButtonListStyle styleBl)
{
    ButtonsList* bl = new ButtonsList;
    bl->changes = true;
    bl->first = NULL;
    bl->last = NULL;
    bl->length = 0;
    bl->topLeft = topLeft;
    bl->bkChanged = true;
    bl->style = styleBl;

    Button* b;

    switch (styleBl)
    {
    case MENUBAR_BL:
        for(int i=0; i<length; i++)
        {
            Button* b = initButton(buttonsNames[i], topLeft, types[i], styles[i]);
            addButtonToList(bl, b);
            topLeft.x = b->bottomRight.x;
            bl->bottomRight.x = b->bottomRight.x;
            bl->bottomRight.y = b->bottomRight.y;
        }
        break;
    case SUBMENU1_BL:
        topLeft.x += SUBMENU1_PADDING;
        topLeft.y += SUBMENU1_PADDING;
        int i;
        for(i=0; i<length-1; i++)
        {
            Button* b = initButton(buttonsNames[i], topLeft, types[i], styles[i]);

            addButtonToList(bl, b);
            topLeft.y = b->bottomRight.y + LENGTH_SEPARATOR_BUTTON_BOTTOM;
            bl->bottomRight.x = b->bottomRight.x;
            bl->bottomRight.y = b->bottomRight.y;
        }
        if(length > 0)
        {
            Button* b = initButton(buttonsNames[i], topLeft, types[i], styles[i]);
            addButtonToList(bl, b);
            topLeft.y = b->bottomRight.y;
            bl->bottomRight.x = b->bottomRight.x;
            bl->bottomRight.y = b->bottomRight.y;
        }
        bl->bottomRight.x += SUBMENU1_PADDING;
        bl->bottomRight.y += SUBMENU1_PADDING;
        break;
    case MODAL1_BL:
        b = initButton(buttonsNames[0], topLeft, types[0], styles[0]);
        addButtonToList(bl, b);

        topLeft.x = (MAX_WIDTH + MODAL1_WIDTH) / 2 - MODAL1_PADDING - 2*PADDING_SIDES_MODAL1_BTN - CHAR_WIDTH * MODAL1_CHARS_BUTTON;
        b = initButton(buttonsNames[1], topLeft, types[1], styles[1]);
        addButtonToList(bl, b);

        bl->bottomRight = b->bottomRight;
        break;
    case MODAL2_BL:
        b = initButton(buttonsNames[0], topLeft, types[0], styles[0]);
        addButtonToList(bl, b);

        topLeft.x = (MAX_WIDTH + MODAL2_WIDTH) / 2 - MODAL2_PADDING - 2*PADDING_SIDES_MODAL2_BTN - CHAR_WIDTH * MODAL2_CHARS_BUTTON;
        b = initButton(buttonsNames[1], topLeft, types[1], styles[1]);
        addButtonToList(bl, b);

        bl->bottomRight = b->bottomRight;
        break;
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
        free(aux->text);
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

MenuArea* initMenuArea(Point topLeft, Editor *e)
{
    MenuArea* ma = new MenuArea;
    ma->bkChanges = true;
    ma->e = e;
    ma->separatorLength = 2;
    ma->fileStateChanged = false;

    ma->topLeft = topLeft;

    char buttonsNames[][MAX_NAMES_LEN] = {"File", "Move", "Edit", "Format"};
    ButtonType types[] = {FILE_ACTIONS, MOVE, EDIT, FORMAT};
    ButtonStyle styles[] = {MENUBAR, MENUBAR, MENUBAR, MENUBAR};

    ma->buttonsList = initButtonsList({0, 0}, buttonsNames, types, 4, styles, MENUBAR_BL);
    ma->bottomRight = {MAX_WIDTH, CHAR_HEIGHT + ma->separatorLength + 2*ma->buttonsList->first->paddingTopBottom};

    ma->changes = true;
    return ma;
}

void drawArea(MenuArea *ma)
{
    if(ma->changes == false)
        return;


    if(ma->fileStateChanged == true)
    {
        setbkcolor(convertToBGIColor(MENU_BAR_BK));
        setcolor(convertToBGIColor(MENU_BAR_FONT));
        if(ma->e->textArea->savedChanges == false)
        {
            outtextxy(ma->bottomRight.x - 30, (ma->topLeft.y + CHAR_HEIGHT)/2, "*");
        }
        else
        {
            outtextxy(ma->bottomRight.x - 30, (ma->topLeft.y + CHAR_HEIGHT)/2, " ");

        }

        ma->fileStateChanged = false;
    }


    if(ma->bkChanges)
    {
        setfillstyle(SOLID_FILL, convertToBGIColor(MENU_BAR_BK));
        bar(ma->topLeft.x, ma->topLeft.y, ma->bottomRight.x, ma->bottomRight.y);
        setbkcolor(convertToBGIColor(MENU_BAR_BK));
        setcolor(convertToBGIColor(MENU_BAR_FONT));

        if(strlen(ma->e->textArea->fileName) != 0)
        {
            outtextxy(ma->bottomRight.x - strlen(ma->e->textArea->fileName)*CHAR_WIDTH - 30, (ma->topLeft.y + CHAR_HEIGHT)/2, ma->e->textArea->fileName);
        }
        else
        {
            outtextxy(ma->bottomRight.x - strlen("New file")*CHAR_WIDTH - 30, (ma->topLeft.y + CHAR_HEIGHT)/2, "New file");
        }
        ma->bkChanges = false;
    }

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
    char buttonsNames[][MAX_NAMES_LEN] = {"New", "Open file...", "Save", "Save as..."};
    ButtonType types[] = {NEW_FILE, OPEN_FILE, SAVE_FILE, SAVE_AS_FILE};
    ButtonStyle styles[] = {SUBMENU1, SUBMENU1, SUBMENU1, SUBMENU1};

    b->subMenu = initButtonsList({b->topLeft.x, b->bottomRight.y + ma->separatorLength}, buttonsNames, types, 4, styles, SUBMENU1_BL);
}

void showMoveSubMenu(Button* b, MenuArea* ma)
{
    char buttonsNames[][MAX_NAMES_LEN] = {"Go to line", "Go to column"};
    ButtonType types[] = {GO_TO_LINE, GO_TO_COLUMN};
    ButtonStyle styles[] = {SUBMENU1, SUBMENU1};

    b->subMenu = initButtonsList({b->topLeft.x, b->bottomRight.y + ma->separatorLength}, buttonsNames, types, 2, styles, SUBMENU1_BL);
}

// test
void blabla(Editor* e)
{
}

bool blabla2(TextArea* e, char* x)
{
}
//

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
                    Modal2 *m2;
                    switch (subMenuButton->type)
                    {
                    case SAVE_FILE:
                        if(strlen(e->textArea->fileName)==0)
                        {
                            m2 = initModal2(e, "Save the file on the disk", "This is a new file and in order to save it you\nmust provide a path:", "Save file as...", "Cancel", &saveFile);
                        }
                        else
                        {
                            saveFile(e->textArea, e->textArea->fileName);
                        }
                        break;
                    case NEW_FILE:
                        // TODO
                        cout<<"Fisier nou\n";
                        initModal1(e, "Esti sigur ca vrei sa faci asta?", "bla bla bla\nalt text", &blabla);
                        break;
                    case SAVE_AS_FILE:
                        m2 = initModal2(e, "Save the file on the disk", "To save the file you must provide a path:", "Save file as...", "Cancel", &saveFile);
                        break;
                    case OPEN_FILE:
                        m2 = initModal2(e, "Open a file on the disk", "You must provide the full path to the file:", "Open file", "Cancel", &openFile);
                        break;
                    }

                    deleteButtonsList(currentButton->subMenu);
                    currentButton->subMenu = NULL;
                    currentButton->pressed = false;
                    e->textArea->changes = true;
                    e->textArea->bkChanges = true;
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
            case MOVE:
                showMoveSubMenu(currentButton, ma);
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
            case MOVE:
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
                    e->textArea->bkChanges = true;
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

TextArea* initTextArea(Editor *e, Point topLeft, Point bottomRight)
{
    TextArea* ta = new TextArea;
    ta->e = e;
    ta->fileName[0]='\0';
    ta->unixFile = false;
    ta->savedChanges = true;
    ta->bkChanges = true;
    ta->numbersDisplayed = true;

    ta->topLeftWindow = topLeft;
    ta->bottomRightWindow = bottomRight;

    ta->topLeft = {topLeft.x + CHAR_WIDTH/4, topLeft.y+ CHAR_WIDTH/4};
    ta->bottomRight = {bottomRight.x, bottomRight.y};


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
    ta->maxLines = abs(ta->bottomRight.y - ta->topLeft.y) / CHAR_HEIGHT;
    ta->maxCharLine = abs(ta->bottomRight.x - ta->topLeft.x) / CHAR_WIDTH;

    return ta;
}

TextArea* initTextArea(Editor* e, Point topLeft, Point bottomRight, char *fileName)
{
    TextArea* ta = new TextArea;
    ta->e = e;
    ta->fileName[0]='\0';
    ta->savedChanges = true;
    ta->unixFile = false;
    ta->changes = true;
    ta->firstLine = 0;
    ta->bkChanges = true;
    ta->numbersDisplayed = true;

    ta->topLeftWindow = topLeft;
    ta->bottomRightWindow = bottomRight;

    ta->topLeft = {topLeft.x + CHAR_WIDTH/4, topLeft.y+ CHAR_WIDTH/4};
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

void handleScroll(TextArea *ta)
{
    if(ta->cursor->position.x<0)
    {
        ta->firstColumn += ta->cursor->position.x;
        ta->cursor->position.x = 0;
        ta->changes = true;
    }

    if(ta->cursor->position.x>=ta->maxCharLine)
    {
        ta->firstColumn += ta->cursor->position.x - ta->maxCharLine + 1;
        ta->cursor->position.x = ta->maxCharLine-1;
        ta->changes = true;
    }

    if(ta->cursor->position.y<0)
    {
        ta->firstLine += ta->cursor->position.y;
        ta->cursor->position.y = 0;
        ta->changes = true;
    }

    if(ta->cursor->position.y>=ta->maxLines)
    {
        ta->firstLine += ta->cursor->position.y - ta->maxLines + 1;
        ta->cursor->position.y = ta->maxLines-1;
        ta->changes = true;
    }
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
        ta->cursor->pieceTableNode = ta->pieceTable->nodesList->last;
        ta->cursor->positionInNode = ta->cursor->pieceTableNode->length;
        updateCursorPosition(ta);
        handleScroll(ta);
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
    handleScroll(ta);
}

void moveCursor(TextArea *ta, Point dest)
{
    if(dest.x+(int)ta->firstColumn<0 || dest.y+(int)ta->firstLine<0)
        return;

    drawCursorLine(ta,true);
    getCursorPositionInPiecetable(ta,dest);
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

void updateCursorPosition(TextArea *ta)
{
    Point dest = {0,0};
    PieceTableNode *ptn = ta->cursor->pieceTableNode;
    int i = ta->cursor->positionInNode-1;

    while(ptn!=NULL && (i<0 || ptn->buffer->text[ptn->start+i]!='\n'))
    {
        if(i<0)
        {
            ptn = ptn->prev;
            if(ptn!=NULL)
                i = ptn->length;
        }
        else if(ptn->buffer->text[ptn->start+i]!='\n')
            dest.x++;
        i--;
    }

    if(i<0 && ptn!=NULL)
    {
        ptn = ptn->prev;
        if(ptn!=NULL)
            i = ptn->length-1;
    }
    if(ptn!=NULL)
    {
        while(i>=0)
        {
            if(ptn->buffer->text[ptn->start+i]=='\n')
                dest.y++;
            i--;
        }
        ptn = ptn->prev;
    }

    while(ptn!=NULL)
    {
        dest.y += ptn->numberNewLines;
        ptn = ptn->prev;
    }

    ta->cursor->position = {dest.x - (int)ta->firstColumn, dest.y - (int)ta->firstLine};
    handleScroll(ta);
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
            c->pieceTableNode->numberNewLines++;
            ta->pieceTable->numberOfLines++;
        }
        updateCursorPosition(ta);
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
            ta->pieceTable->numberOfLines++;
        c->pieceTableNode = newNode;
        c->positionInNode = 1;
        updateCursorPosition(ta);
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
            ta->pieceTable->numberOfLines++;
        c->pieceTableNode = newNode;
        c->positionInNode = 1;
        updateCursorPosition(ta);
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
            ta->pieceTable->numberOfLines++;
        c->pieceTableNode = newNode;
        c->positionInNode = 1;
        ta->pieceTable->nodesList->length+=2;
        updateCursorPosition(ta);
        return;
    }
}

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
    settextstyle(0, HORIZ_DIR, 2);

    setbkcolor(WHITE);
    setcolor(BLACK);
    cleardevice();

    Editor *e = new Editor;
    e->running = true;

    Point topLeft, bottomRight;

    topLeft= {0, 0};
    e->menuArea = initMenuArea(topLeft, e);

    topLeft= {0,0};
    bottomRight = {MAX_WIDTH,MAX_HEIGHT};

    //
    // e->scrollBarsArea = initScrollBarsArea(topLeft, bottomRight);
    // De mutat in initTextArea

    topLeft= {0, e->menuArea->bottomRight.y};
    bottomRight = {MAX_WIDTH,MAX_HEIGHT};

    //e->textArea = initTextArea(e, topLeft, bottomRight, "textText.txt");
    e->textArea = initTextArea(e, topLeft, bottomRight);

    e->modalOpen = false;
    e->m1 = NULL;

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

    if(ta->bkChanges)
    {
        setfillstyle(1, convertToBGIColor(TEXTAREA_BK_NORMAL));
        bar(ta->topLeftWindow.x, ta->topLeftWindow.y, ta->bottomRightWindow.x, ta->bottomRightWindow.y);


        if(ta->numbersDisplayed)
        {
            ta->maxCharLine = abs(ta->bottomRight.x - ta->topLeft.x - numberOfChar(ta->pieceTable->numberOfLines + 1)) / CHAR_WIDTH;
            setbkcolor(convertToBGIColor(TEXTAREA_BK_NORMAL));
            setcolor(convertToBGIColor(TEXTAREA_NUMBERS_COLOR));

            ta->topLeft.x = ta->topLeftWindow.x + numberOfChar(ta->pieceTable->numberOfLines + 1) * CHAR_WIDTH + CHAR_WIDTH/2 + 1;
            ta->topLeftNumbers.x = CHAR_WIDTH/4 + ta->topLeftWindow.x;
            ta->topLeftNumbers.y = ta->topLeft.y;
            ta->bottomRightNumbers.x = ta->topLeftNumbers.x + numberOfChar(ta->pieceTable->numberOfLines + 1) * CHAR_WIDTH + 1;
            ta->bottomRightNumbers.y = ta->bottomRight.y;

            line(ta->bottomRightNumbers.x, ta->topLeftNumbers.y, ta->bottomRightNumbers.x, ta->bottomRightNumbers.y);

            int tmp = ta->firstLine;
            int x = ta->topLeftNumbers.x;
            int y = ta->topLeftNumbers.y;
            int size_char = numberOfChar(ta->pieceTable->numberOfLines + 1);
            while(tmp <= ta->pieceTable->numberOfLines && (ta->maxLines + ta->firstLine - tmp) > 0)
            {
                char *text = itoa(tmp + 1, size_char);

                outtextxy(x, y, text);
                free(text);
                tmp+=1;
                y+=CHAR_HEIGHT;
            }
        }

        // ta->bkChanges = false;
    }

    int current_y=ta->topLeft.y;
    long showedLines = 0;
    long currentLine = ta->firstLine;

    drawLines(ta, current_y, ta->bottomRight.y);

    drawCursorLine(ta);
}

bool openFile(TextArea *ta, char *fileName)
{
    FILE *file = fopen(fileName, "rb");

    if(file == NULL)
    {
        fclose(file);
        printf("Eroare la citirea fisierului!\n");
        return true;
    }

    strcpy(ta->fileName, fileName);
    ta->e->menuArea->bkChanges = true;
    ta->e->menuArea->changes = true;
    for(Button *b=ta->e->menuArea->buttonsList->first; b != NULL; b = b->next)
    {
        b->changes = true;
    }

    emptyPieceTable(ta->pieceTable);
    ta->firstColumn = 0;
    ta->firstLine = 0;

    bool unixFile = false;
    unsigned int readSize;
    char lastAddedChar = '\0';
    int numberOfSpaces = 0;
    bool ok = false;
    ta->pieceTable->numberOfLines = 0;

    do
    {
        char last_x;
        if(fread(&last_x, sizeof(char), 1, file) == 0)
        {
            last_x = '\0';
            readSize = 0;
        }
        Buffer *newBuffer=NULL;
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

        while(newBuffer != NULL && (newBuffer->length < MAX_LENGTH_BUFFER) && fread(&x, sizeof(char), 1, file))
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
    PieceTableNode *newPtn = initPieceTableNode(newBuffer, 0, 0, 0);
    addPieceTableNode(ta->pieceTable->nodesList, newPtn);

    ta->cursor->position = {0, 0};
    ta->cursor->pieceTableNode = ta->pieceTable->nodesList->first;
    ta->cursor->positionInNode = 0;

    fclose(file);
    return false;
}

bool saveFile(TextArea *ta, char *fileName)
{
    FILE *file = fopen(fileName, "wb");

    if(file == NULL)
    {
        fclose(file);
        printf("Eroare la scrierea fisierului!\n");
        return true;
    }


    strcpy(ta->fileName, fileName);
    ta->e->menuArea->bkChanges = true;
    ta->e->menuArea->changes = true;
    for(Button *b=ta->e->menuArea->buttonsList->first; b != NULL; b = b->next)
    {
        b->changes = true;
    }
    ta->savedChanges = true;
    ta->e->menuArea->changes = true;
    ta->e->menuArea->fileStateChanged = true;

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
    return false;
}

void drawEditor(Editor *e)
{
    drawArea(e->textArea);
    drawArea(e->menuArea);
    if(e->modalOpen)
    {
        if(e->m1 != NULL)
        {
            drawModal1(e->m1);
        }
        if(e->m2 != NULL)
        {
            drawModal2(e->m2);
        }
    }
    //drawArea(e->scrollBarsArea);
    e->textArea->changes = false;
}

void stopEditor(Editor *e)
{
    e->running = false;
    closegraph();
    // TODO: Delete data from memory
}

Modal1* initModal1(Editor *e, char *title, char *description, void (*action)(Editor*))
{
    e->modalOpen = true;

    Modal1 *m1 = new Modal1;
    e->m1 = m1;
    m1->changes = true;
    m1->bkChanges = true;

    m1->topLeft.x = (MAX_WIDTH - MODAL1_WIDTH) / 2;
    m1->topLeft.y = (MAX_HEIGHT - MODAL1_HEIGHT) / 2;
    m1->bottomRight.x = m1->topLeft.x + MODAL1_WIDTH;
    m1->bottomRight.y = m1->topLeft.y + MODAL1_HEIGHT;

    m1->title = (char*) malloc(sizeof(char) * strlen(title));
    strcpy(m1->title, title);
    m1->description = (char*) malloc(sizeof(char) * strlen(description));
    strcpy(m1->description, description);

    char buttonsNames[][MAX_NAMES_LEN] = {"Confirm", "Cancel"};
    ButtonType types[] = {MODAL1_CONFIRM, MODAL1_CANCEL};
    ButtonStyle styles[] = {MODAL1_CONFIRM_STYLE, MODAL1_CANCEL_STYLE};

    m1->bl = initButtonsList({m1->topLeft.x + MODAL1_PADDING, m1->bottomRight.y - MODAL1_PADDING - CHAR_HEIGHT - 2*PADDING_TOP_BOTTOM_MODAL1_BTN},
                             buttonsNames, types, 2, styles, MODAL1_BL);

    m1->action = action;
    m1->e = e;
    return m1;
}

void deleteModal1(Modal1 *m1)
{
    free(m1->title);
    free(m1->description);
    m1->e->m1 = NULL;
    m1->e->modalOpen = false;
    m1->e->textArea->changes = true;
    deleteButtonsList(m1->bl);
    delete m1;
}

void drawModal1(Modal1 *m1)
{
    if(!m1->changes) return;

    if(m1->bkChanges)
    {
        setfillstyle(SOLID_FILL, convertToBGIColor(MODAL1_SHADOW));
        bar(m1->topLeft.x + MODAL1_SHADOW_OFF, m1->topLeft.y+ MODAL1_SHADOW_OFF, m1->bottomRight.x+ MODAL1_SHADOW_OFF, m1->bottomRight.y+ MODAL1_SHADOW_OFF);
        setfillstyle(SOLID_FILL, convertToBGIColor(MODAL1_BK_NORMAL));
        bar(m1->topLeft.x, m1->topLeft.y, m1->bottomRight.x, m1->bottomRight.y);

        Point topLeft = m1->topLeft;
        topLeft.x += MODAL1_PADDING;
        topLeft.y += MODAL1_PADDING;

        setbkcolor(convertToBGIColor(MODAL1_BK_NORMAL));
        setcolor(convertToBGIColor(MODAL1_FONT_NORMAL));

        char *p = strtok(m1->title, "\n");
        while(p)
        {
            outtextxy(topLeft.x, topLeft.y, p);
            p = strtok(NULL, "\n");
            topLeft.y += CHAR_HEIGHT;
        }

        topLeft.y += CHAR_HEIGHT;

        p = strtok(m1->description, "\n");
        while(p)
        {
            outtextxy(topLeft.x, topLeft.y, p);
            p = strtok(NULL, "\n");
            topLeft.y += CHAR_HEIGHT;
        }

        m1->bkChanges = false;
    }

    drawButtonsList(m1->bl);
    m1->changes = false;
}

void handleClick(Modal1 *m1, int x, int y)
{
    for(Button* currentButton = m1->bl->first; currentButton != NULL; currentButton = currentButton->next)
    {
        if(cursorInArea(currentButton, x, y) && currentButton->pressed == false)
        {
            switch (currentButton->type)
            {
            case MODAL1_CONFIRM:
                cout<<"CONFIRMAT\n";
                break;
            }

            deleteModal1(m1);
            return;
        }
    }
}

void handleHover(Modal1 *m1, int x, int y)
{
    for(Button* currentButton = m1->bl->first; currentButton != NULL; currentButton = currentButton->next)
    {
        if(cursorInArea(currentButton, x, y) && currentButton->hovered == false)
        {
            currentButton->hovered = true;
            currentButton->changes = true;
            m1->changes = true;
        }
    }
}

void clearHover(Modal1 *m1, int x, int y)
{
    for(Button* currentButton = m1->bl->first; currentButton != NULL; currentButton = currentButton->next)
    {

        if(!cursorInArea(currentButton, x, y) && currentButton->hovered == true)
        {
            currentButton->hovered = false;
            currentButton->changes = true;
            m1->changes = true;
        }
    }
}

CursorModal2* initCursorModal2(Point position, InputModal2 *input)
{
    CursorModal2 *cursor = new CursorModal2;
    cursor->input = input;
    cursor->position = position;
    cursor->state = false;
    cursor->lastUpdate = 0;
    return cursor;
}

void deleteCursorModal2(CursorModal2* cursor)
{
    delete cursor;
}

void changeCursor(CursorModal2* cursor)
{
    if(cursor->state)
    {
        cursor->state = false;
    }
    else
    {
        cursor->state = true;
    }

    cursor->input->changes = true;
    cursor->input->modal->changes = true;
    cursor->lastUpdate = time(0);
}

void drawCursorModal2(CursorModal2 *cursor)
{
    if(cursor->state)
    {
        setcolor(convertToBGIColor(INPUT_MODAL2_CURSOR_COLOR));
    }
    else
    {
        setcolor(convertToBGIColor(INPUT_MODAL2_FOCUSED_BK));
    }
    line(cursor->position.x, cursor->position.y, cursor->position.x, cursor->position.y + CHAR_HEIGHT - 1);
}

InputModal2* initInputModal2(Point topLeft, Point bottomRight, Modal2* modal)
{
    InputModal2 *input = new InputModal2;
    input->modal = modal;
    input->topLeft = topLeft;
    input->bottomRight = bottomRight;
    input->changes = true;
    input->state = false;
    input->text[0] = '\0';
    input->cursor = initCursorModal2({topLeft.x + INPUT_MODAL2_MARGIN_SIZE + INPUT_MODAL2_PADDING, topLeft.y + INPUT_MODAL2_MARGIN_SIZE + INPUT_MODAL2_PADDING}, input);
    return input;
}

void deleteInputModal2(InputModal2* input)
{
    deleteCursorModal2(input->cursor);
    delete input;
}

void drawInputModal2(InputModal2 *input)
{
    if(!input->changes) return;

    if(input->state)
    {
        // Draw the margins
        setfillstyle(1, convertToBGIColor(INPUT_MODAL2_MARGIN_FOCUSED));
        bar(input->topLeft.x, input->topLeft.y, input->bottomRight.x, input->topLeft.y + INPUT_MODAL2_MARGIN_SIZE);
        bar(input->topLeft.x, input->topLeft.y, input->topLeft.x + INPUT_MODAL2_MARGIN_SIZE, input->bottomRight.y);
        bar(input->bottomRight.x, input->topLeft.y, input->bottomRight.x - INPUT_MODAL2_MARGIN_SIZE, input->bottomRight.y);
        bar(input->topLeft.x, input->bottomRight.y, input->bottomRight.x, input->bottomRight.y - INPUT_MODAL2_MARGIN_SIZE);

        setfillstyle(1, convertToBGIColor(INPUT_MODAL2_FOCUSED_BK));
        bar(input->topLeft.x + INPUT_MODAL2_MARGIN_SIZE, input->topLeft.y + INPUT_MODAL2_MARGIN_SIZE, input->bottomRight.x - INPUT_MODAL2_MARGIN_SIZE, input->bottomRight.y - INPUT_MODAL2_MARGIN_SIZE);

        setbkcolor(convertToBGIColor(INPUT_MODAL2_FOCUSED_BK));
        setcolor(convertToBGIColor(INPUT_MODAL2_FOCUSED_FONT));
        outtextxy(input->topLeft.x + INPUT_MODAL2_MARGIN_SIZE + INPUT_MODAL2_PADDING, input->topLeft.y + INPUT_MODAL2_MARGIN_SIZE + INPUT_MODAL2_PADDING, input->text);

        drawCursorModal2(input->cursor);
    }
    else
    {
        // Draw the margins
        setfillstyle(1, convertToBGIColor(INPUT_MODAL2_MARGIN_COLOR));
        bar(input->topLeft.x, input->topLeft.y, input->bottomRight.x, input->topLeft.y + INPUT_MODAL2_MARGIN_SIZE);
        bar(input->topLeft.x, input->topLeft.y, input->topLeft.x + INPUT_MODAL2_MARGIN_SIZE, input->bottomRight.y);
        bar(input->bottomRight.x, input->topLeft.y, input->bottomRight.x - INPUT_MODAL2_MARGIN_SIZE, input->bottomRight.y);
        bar(input->topLeft.x, input->bottomRight.y, input->bottomRight.x, input->bottomRight.y - INPUT_MODAL2_MARGIN_SIZE);

        setfillstyle(1, convertToBGIColor(INPUT_MODAL2_NORMAL_BK));
        bar(input->topLeft.x + INPUT_MODAL2_MARGIN_SIZE, input->topLeft.y + INPUT_MODAL2_MARGIN_SIZE, input->bottomRight.x - INPUT_MODAL2_MARGIN_SIZE, input->bottomRight.y - INPUT_MODAL2_MARGIN_SIZE);

        setbkcolor(convertToBGIColor(INPUT_MODAL2_NORMAL_BK));
        setcolor(convertToBGIColor(INPUT_MODAL2_NORMAL_FONT));
        outtextxy(input->topLeft.x + INPUT_MODAL2_MARGIN_SIZE + INPUT_MODAL2_PADDING, input->topLeft.y + INPUT_MODAL2_MARGIN_SIZE + INPUT_MODAL2_PADDING, input->text);

    }
    input->changes = false;
}

bool cursorInArea(InputModal2* input, int x, int y)
{
    return input->topLeft.x < x && x < input->bottomRight.x && input->topLeft.y < y && y < input->bottomRight.y;
}

void addCharToModal2Input(InputModal2* input, char x)
{
    unsigned int lg = strlen(input->text);
    if(lg >= MAX_CHAR_MODAL2_INPUT) return;

    input->text[lg] = x;
    input->text[lg+1] = '\0';
    input->cursor->position.x += CHAR_WIDTH;
    input->cursor->state = true;
    input->cursor->lastUpdate = time(0);
    input->changes = true;
    input->modal->changes = true;
}

void deleteCharFromModal2Input(InputModal2* input)
{
    unsigned int lg = strlen(input->text);
    if(lg == 0) return;

    input->text[lg-1] = '\0';
    input->cursor->position.x -= CHAR_WIDTH;
    input->cursor->state = true;
    input->cursor->lastUpdate = time(0);
    input->changes = true;
    input->modal->changes = true;
}

Modal2* initModal2(Editor *e, char *title, char *description, char *buttonNameYes, char *buttonNameNo, bool (*action)(TextArea*, char*))
{
    e->modalOpen = true;

    Modal2 *m2 = new Modal2;
    e->m2 = m2;
    m2->error = false;
    m2->errorMessageChanges = false;

    m2->changes = true;
    m2->bkChanges = true;

    m2->topLeft.x = (MAX_WIDTH - MODAL2_WIDTH) / 2;
    m2->topLeft.y = (MAX_HEIGHT - MODAL2_HEIGHT) / 2;
    m2->bottomRight.x = m2->topLeft.x + MODAL2_WIDTH;
    m2->bottomRight.y = m2->topLeft.y + MODAL2_HEIGHT;

    m2->title = (char*) malloc(sizeof(char) * strlen(title));
    strcpy(m2->title, title);
    m2->description = (char*) malloc(sizeof(char) * strlen(description));
    strcpy(m2->description, description);

    char buttonsNames[2][MAX_NAMES_LEN];
    strcpy(buttonsNames[0], buttonNameYes);
    strcpy(buttonsNames[1], buttonNameNo);

    ButtonType types[] = {MODAL2_CONFIRM, MODAL2_CANCEL};
    ButtonStyle styles[] = {MODAL2_CONFIRM_STYLE, MODAL2_CANCEL_STYLE};

    m2->bl = initButtonsList({(MAX_WIDTH + MODAL2_WIDTH) / 2 - MODAL2_PADDING - 4*PADDING_SIDES_MODAL2_BTN - CHAR_WIDTH * max((int)strlen(buttonsNames[1]),MODAL2_CHARS_BUTTON) - 2*CHAR_WIDTH - CHAR_WIDTH * max((int)strlen(buttonsNames[0]),MODAL2_CHARS_BUTTON),
                              m2->bottomRight.y - MODAL2_PADDING - CHAR_HEIGHT - 2*PADDING_TOP_BOTTOM_MODAL2_BTN},
                             buttonsNames, types, 2, styles, MODAL2_BL);
    m2->iM = initInputModal2({m2->topLeft.x + MODAL2_PADDING, m2->bottomRight.y - MODAL2_PADDING - 3*CHAR_HEIGHT - 2*PADDING_TOP_BOTTOM_MODAL2_BTN - 2*INPUT_MODAL2_PADDING - 2*INPUT_MODAL2_MARGIN_SIZE},
    {m2->bottomRight.x - MODAL2_PADDING, m2->bottomRight.y - MODAL2_PADDING - 2*CHAR_HEIGHT - 2*PADDING_TOP_BOTTOM_MODAL2_BTN}, m2);

    m2->action = action;
    m2->e = e;
    return m2;
}

void deleteModal2(Modal2 *m2)
{
    free(m2->title);
    free(m2->description);
    free(m2->errorMessage);
    m2->e->m2 = NULL;
    m2->e->modalOpen = false;
    m2->e->textArea->changes = true;
    deleteButtonsList(m2->bl);
    deleteInputModal2(m2->iM);
    delete m2;
}

void drawModal2(Modal2 *m2)
{
    if(!m2->changes) return;

    if(m2->bkChanges)
    {
        setfillstyle(SOLID_FILL, convertToBGIColor(MODAL2_SHADOW));
        bar(m2->topLeft.x + MODAL2_SHADOW_OFF, m2->topLeft.y+ MODAL2_SHADOW_OFF, m2->bottomRight.x+ MODAL2_SHADOW_OFF, m2->bottomRight.y+ MODAL2_SHADOW_OFF);
        setfillstyle(SOLID_FILL, convertToBGIColor(MODAL2_BK_NORMAL));
        bar(m2->topLeft.x, m2->topLeft.y, m2->bottomRight.x, m2->bottomRight.y);

        Point topLeft = m2->topLeft;
        topLeft.x += MODAL2_PADDING;
        topLeft.y += MODAL2_PADDING;

        setbkcolor(convertToBGIColor(MODAL2_BK_NORMAL));
        setcolor(convertToBGIColor(MODAL2_FONT_NORMAL));

        char *p = strtok(m2->title, "\n");
        while(p)
        {
            outtextxy(topLeft.x, topLeft.y, p);
            p = strtok(NULL, "\n");
            topLeft.y += CHAR_HEIGHT;
        }

        topLeft.y += CHAR_HEIGHT;

        p = strtok(m2->description, "\n");
        while(p)
        {
            outtextxy(topLeft.x, topLeft.y, p);
            p = strtok(NULL, "\n");
            topLeft.y += CHAR_HEIGHT;
        }

        m2->bkChanges = false;
    }

    if(m2->errorMessageChanges && m2->error)
    {
        setfillstyle(SOLID_FILL, convertToBGIColor(MODAL2_BK_NORMAL));
        setbkcolor(convertToBGIColor(MODAL2_BK_NORMAL));
        setcolor(convertToBGIColor(MODAL2_ERROR_MSG_COLOR));

        bar(m2->iM->topLeft.x, m2->iM->topLeft.y - 2*CHAR_HEIGHT, m2->iM->bottomRight.x, m2->iM->topLeft.y - 1*CHAR_HEIGHT);
        outtextxy(m2->iM->topLeft.x, m2->iM->topLeft.y - 2*CHAR_HEIGHT, m2->errorMessage);
    }

    drawButtonsList(m2->bl);
    drawInputModal2(m2->iM);
    m2->changes = false;
}

void setErrorMessageModal2(Modal2 *m2, char *message)
{
    m2->error = true;
    m2->errorMessage= (char*) malloc(sizeof(char) * strlen(message));
    strcpy(m2->errorMessage, message);
    m2->errorMessageChanges = true;
    m2->changes = true;
}

void handleClick(Modal2 *m2, int x, int y)
{
    if(cursorInArea(m2->iM, x, y) && m2->iM->state == false)
    {
        m2->iM->state = true;
        m2->iM->changes = true;
        m2->changes = true;
    }

    for(Button* currentButton = m2->bl->first; currentButton != NULL; currentButton = currentButton->next)
    {
        if(cursorInArea(currentButton, x, y) && currentButton->pressed == false)
        {
            bool error = false;
            switch (currentButton->type)
            {
            case MODAL2_CONFIRM:
                error = m2->action(m2->e->textArea, m2->iM->text);
                if(strlen(m2->iM->text) == 0)
                {
                    setErrorMessageModal2(m2, "The input can't be empty!");
                    return;
                }
                if(error)
                {
                    setErrorMessageModal2(m2, "There was a problem with your input!");
                    return;
                }
                cout<<"CONFIRMAT\n";
                break;
            }

            deleteModal2(m2);
            return;
        }
    }
}


void handleHover(Modal2 *m2, int x, int y)
{
    for(Button* currentButton = m2->bl->first; currentButton != NULL; currentButton = currentButton->next)
    {
        if(cursorInArea(currentButton, x, y) && currentButton->hovered == false)
        {
            currentButton->hovered = true;
            currentButton->changes = true;
            m2->changes = true;
        }
    }
}

void clearHover(Modal2 *m2, int x, int y)
{
    for(Button* currentButton = m2->bl->first; currentButton != NULL; currentButton = currentButton->next)
    {

        if(!cursorInArea(currentButton, x, y) && currentButton->hovered == true)
        {
            currentButton->hovered = false;
            currentButton->changes = true;
            m2->changes = true;
        }
    }
}

void clearClick(Modal2 *m2, int x, int y)
{
    if(!cursorInArea(m2->iM, x, y) && m2->iM->state == true)
    {
        m2->iM->state = false;
        m2->iM->changes = true;
        m2->changes = true;
    }
}

