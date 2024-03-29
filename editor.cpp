#include <graphics.h>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <ctime>
#include <cstdlib>

#include "editor.h"
#include "helpers.h"

Button* initButton(char *name, Point topLeft, ButtonType type, ButtonStyle style)
{
    Button *b = new Button;
    b->subMenu = NULL;
    b->pressed = false;
    b->active = true;


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


        b->lengthText = std::max(int(strlen(name)), MODAL2_CHARS_BUTTON) * CHAR_WIDTH;
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

    if(!b->active)
    {
        setfillstyle(SOLID_FILL, convertToBGIColor(INACTIVE_BUTTON_BK));
        setbkcolor(convertToBGIColor(INACTIVE_BUTTON_BK));
        setcolor(convertToBGIColor(INACTIVE_BUTTON_FONT));
        bar(b->topLeft.x, b->topLeft.y,  b->bottomRight.x, b->bottomRight.y);
        outtextxy(b->topLeft.x + b->paddingSides, b->topLeft.y + b->paddingTopBottom, b->text);
        b->changes = false;
        return;
    }

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

    char buttonsNames[][MAX_NAMES_LEN] = {"File", "Move", "Options"};
    ButtonType types[] = {FILE_ACTIONS, MOVE, OPTIONS};
    ButtonStyle styles[] = {MENUBAR, MENUBAR, MENUBAR};

    ma->buttonsList = initButtonsList({0, 0}, buttonsNames, types, 3, styles, MENUBAR_BL);
    ma->bottomRight = {MAX_WIDTH, CHAR_HEIGHT + ma->separatorLength + 2*ma->buttonsList->first->paddingTopBottom};

    ma->changes = true;
    return ma;
}

void drawArea(MenuArea *ma)
{
    if(ma->changes == false)
        return;


    if(ma->bkChanges)
    {
        setfillstyle(SOLID_FILL, convertToBGIColor(MENU_BAR_BK));
        bar(ma->topLeft.x, ma->topLeft.y, ma->bottomRight.x, ma->bottomRight.y);
        setbkcolor(convertToBGIColor(MENU_BAR_BK));
        setcolor(convertToBGIColor(MENU_BAR_FONT));

        if(strlen(ma->e->textArea->fileName) != 0)
        {
            outtextxy(ma->bottomRight.x - strlen(ma->e->textArea->fileName)*CHAR_WIDTH - 30, ma->topLeft.y +  PADDING_TOP_BOTTOM_MENU_BAR_BUTTON, ma->e->textArea->fileName);
        }
        else
        {
            outtextxy(ma->bottomRight.x - strlen("New file")*CHAR_WIDTH - 30, ma->topLeft.y + PADDING_TOP_BOTTOM_MENU_BAR_BUTTON, "New file");
        }
        ma->bkChanges = false;
    }

    setfillstyle(SOLID_FILL, convertToBGIColor(MENU_BAR_SEPARATOR_BAR));
    bar(ma->topLeft.x, ma->bottomRight.y - ma->separatorLength, ma->bottomRight.x, ma->bottomRight.y);


    if(ma->fileStateChanged == true)
    {
        setbkcolor(convertToBGIColor(MENU_BAR_BK));
        setcolor(convertToBGIColor(MENU_BAR_FONT));
        if(ma->e->textArea->savedChanges == false)
        {
            outtextxy(ma->bottomRight.x - 30, ma->topLeft.y +  PADDING_TOP_BOTTOM_MENU_BAR_BUTTON, "*");
        }
        else
        {
            outtextxy(ma->bottomRight.x - 30, ma->topLeft.y +  PADDING_TOP_BOTTOM_MENU_BAR_BUTTON, " ");

        }

        ma->fileStateChanged = false;
    }

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
    char buttonsNames[][MAX_NAMES_LEN] = {"Close window", "New window", "Open file...", "Save", "Save as..."};
    ButtonType types[] = {CLOSE_WINDOW, NEW_WINDOW, OPEN_FILE, SAVE_FILE, SAVE_AS_FILE};
    ButtonStyle styles[] = {SUBMENU1, SUBMENU1, SUBMENU1, SUBMENU1, SUBMENU1};

    b->subMenu = initButtonsList({b->topLeft.x, b->bottomRight.y + ma->separatorLength}, buttonsNames, types, 5, styles, SUBMENU1_BL);
}

void showMoveSubMenu(Button* b, MenuArea* ma)
{
    char buttonsNames[][MAX_NAMES_LEN] = {"Go to line", "Go to column", "Go to end of line", "Go to start of line"};
    ButtonType types[] = {GO_TO_LINE, GO_TO_COLUMN, GO_TO_END_LINE, GO_TO_START_LINE};
    ButtonStyle styles[] = {SUBMENU1, SUBMENU1, SUBMENU1, SUBMENU1};

    b->subMenu = initButtonsList({b->topLeft.x, b->bottomRight.y + ma->separatorLength}, buttonsNames, types, 4, styles, SUBMENU1_BL);
}

void showOptionsSubMenu(Button* b, MenuArea* ma)
{
    char buttonsNames[][MAX_NAMES_LEN] = {"Show lines", "Hide lines", "Change to vertical", "Change to horizontal"};
    ButtonType types[] = {SHOW_LINES, HIDE_LINES, SWITCH_ORIENTATION_V, SWITCH_ORIENTATION_H};
    ButtonStyle styles[] = {SUBMENU1, SUBMENU1, SUBMENU1, SUBMENU1};

    b->subMenu = initButtonsList({b->topLeft.x, b->bottomRight.y + ma->separatorLength}, buttonsNames, types, 4, styles, SUBMENU1_BL);

    if(ma->e->textArea->numbersDisplayed == true)
    {
        b->subMenu->first->active = false;
    }
    else
    {
        b->subMenu->first->next->active = false;
    }
}

void deleteTextArea(TextArea *ta)
{
    emptyPieceTable(ta->pieceTable);
    delete ta->cursor;
    delete ta;
}

void closeWindowEditor(TextArea *ta)
{
    TextAreaNodeTreeList *parentList = ta->node->parentList;
    Editor *e = parentList->e;
    if(parentList->length == 1)
    {
        if(parentList->parent == ta->e->root)
        {
            initModal1(ta->e, "Close editor", "This is the last window and\neditor will be closed. \nAre you sure?", STOP_EDITOR);
        }
        else
        {
            TextAreaNodeTree *parentNode = parentList->parent;
            TextAreaNodeTree *aux;
            TextAreaNodeTreeList *parentList = parentNode->parentList;
            if(getNodePositionInTANTL(parentList, parentNode) == 0)
            {
                TextAreaNodeTree *next = parentNode->next;
                parentList->first = parentNode->next;

                delete ta->node;
                delete parentNode->tantl;
                delete parentNode;

                TextAreaNodeTree *nextNodeForArea = next;
                while(nextNodeForArea->type != LEAF_NODE) nextNodeForArea = nextNodeForArea->tantl->first;

                parentList->e->textArea = nextNodeForArea->ta;
                parentList->length--;

                deleteTextArea(ta);
                next->e->root->changes = true;
                aux = next;
            }
            else
            {
                TextAreaNodeTree *prev = parentNode->prev;
                parentNode->prev->next = parentNode->next;
                if(parentNode->next) parentNode->next->prev = parentNode->prev;

                delete ta->node;
                delete parentNode->tantl;
                delete parentNode;

                TextAreaNodeTree *nextNodeForArea = prev;
                while(nextNodeForArea->type != LEAF_NODE) nextNodeForArea = nextNodeForArea->tantl->first;

                parentList->e->textArea = nextNodeForArea->ta;
                parentList->length--;

                deleteTextArea(ta);
                prev->e->root->changes = true;
                aux = prev;
            }

            if(parentList->length == 1)
            {
                if(aux->type == ORIENTATION)
                {
                    aux->parentList->parent->orientation = aux->orientation;
                    aux->parentList->parent->tantl = aux->tantl;
                    aux->tantl->parent = aux->parentList->parent;
                    delete aux;
                }
                else
                {
                    parentList->first = aux;
                    parentList->last = aux;
                }
            }
        }
    }
    else
    {
        TextAreaNodeTree *aux;
        if(getNodePositionInTANTL(parentList, ta->node) == 0)
        {
            TextAreaNodeTree *next = ta->node->next;
            parentList->first = parentList->first->next;
            delete ta->node;

            TextAreaNodeTree *nextNodeForArea = next;
            while(nextNodeForArea->type != LEAF_NODE) nextNodeForArea = nextNodeForArea->tantl->first;
            parentList->e->textArea = nextNodeForArea->ta;

            deleteTextArea(ta);
            parentList->length--;
            parentList->e->root->changes = true;
            aux = next;
        }
        else
        {
            TextAreaNodeTree *prev = ta->node->prev;
            ta->node->prev->next = ta->node->next;
            if(ta->node->next) ta->node->next->prev = ta->node->prev;
            delete ta->node;

            TextAreaNodeTree *nextNodeForArea = prev;
            while(nextNodeForArea->type != LEAF_NODE) nextNodeForArea = nextNodeForArea->tantl->first;
            parentList->e->textArea = nextNodeForArea->ta;

            deleteTextArea(ta);
            parentList->length--;
            parentList->e->root->changes = true;

            if(prev->next == NULL)
            {
                parentList->last = prev;
            }
            aux = prev;
        }

        if(parentList->length == 1)
        {
            if(aux->type == ORIENTATION)
            {
                aux->parentList->parent->orientation = aux->orientation;
                aux->parentList->parent->tantl = aux->tantl;
                aux->tantl->parent = aux->parentList->parent;
                delete aux;
            }
            else
            {
                parentList->first = aux;
                parentList->last = aux;
            }
        }
    }


    e->menuArea->fileStateChanged = true;
    for(Button *b=e->menuArea->buttonsList->first; b != NULL; b = b->next)
    {
        b->changes = true;
    }
    e->menuArea->bkChanges = true;
    e->menuArea->changes = true;
}

void switchOrientation(Editor *e, Orientation orientation)
{
    TextAreaNodeTree *node = e->textArea->node;
    if(node->parentList->length == 1)
    {
        node->parentList->parent->orientation = orientation;
    }
    else
    {
        TextAreaNodeTree *newParentNode = initTextAreaNodeTree(e, orientation);
        newParentNode->next = node->next;
        newParentNode->prev = node->prev;
        if(node->prev) node->prev->next = newParentNode;
        if(node->next) node->next->prev = newParentNode;
        if(node == node->parentList->last) node->parentList->last = newParentNode;
        if(node == node->parentList->first) node->parentList->first = newParentNode;
        newParentNode->parentList = node->parentList;
        addNodeToTANTL(newParentNode->tantl, 0, node);
        node->next = NULL;
        node->prev = NULL;
    }
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
                if(cursorInArea(subMenuButton, x, y) && subMenuButton->active)
                {
                    subMenuButton->pressed = true;
                    Modal2 *m2;
                    int positionInTantl;
                    TextAreaNodeTree *newNodeTantl;
                    TextArea *newTa;

                    switch (subMenuButton->type)
                    {
                    case SAVE_FILE:
                        if(strlen(e->textArea->fileName)==0)
                        {
                            m2 = initModal2(e, "Save the file on the disk", "This is a new file and in order to save it you\nmust provide a path:", "Save file as...", "Cancel", SAVE_FILE);
                        }
                        else
                        {
                            saveFile(e->textArea, e->textArea->fileName);
                        }
                        break;
                    case CLOSE_WINDOW:
                        closeWindowEditor(e->textArea);
                        break;
                    case NEW_WINDOW:
                        positionInTantl = getNodePositionInTANTL(e->textArea->node->parentList, e->textArea->node);
                        newTa = initTextArea(e, {0, 0}, {0, 0});
                        newNodeTantl = initTextAreaNodeTree(e, newTa);
                        addNodeToTANTL(e->textArea->node->parentList, positionInTantl + 1, newNodeTantl);

                        setcolor(convertToBGIColor(TEXTAREA_MARGINS_NORMAL));
                        drawBorderTextArea(e->textArea);
                        drawCursorLine(e->textArea, true);
                        e->textArea->cursor->visibleState = false;

                        e->textArea = newTa;
                        e->root->changes = true;

                        e->menuArea->fileStateChanged = true;
                        for(Button *b=e->menuArea->buttonsList->first; b != NULL; b = b->next)
                        {
                            b->changes = true;
                        }
                        e->menuArea->bkChanges = true;
                        e->menuArea->changes = true;
                        break;
                    case SAVE_AS_FILE:
                        m2 = initModal2(e, "Save the file on the disk", "To save the file you must provide a path:", "Save file as...", "Cancel", SAVE_AS_FILE);
                        break;
                    case OPEN_FILE:
                        m2 = initModal2(e, "Open a file on the disk", "You must provide the full path to the file:", "Open file", "Cancel", OPEN_FILE);
                        break;
                    case GO_TO_LINE:
                        m2 = initModal2(e, "Go to a line", "Which line do you want to go?", "Go to line", "Cancel", GO_TO_LINE);
                        break;
                    case GO_TO_COLUMN:
                        m2 = initModal2(e, "Go to a column", "Which column do you want to go?", "Go to column", "Cancel", GO_TO_COLUMN);
                        break;
                    case GO_TO_END_LINE:
                        getCursorPositionInPiecetable(e->textArea, {2000000000, e->textArea->cursor->position.y});
                        break;
                    case GO_TO_START_LINE:
                        getCursorPositionInPiecetable(e->textArea, {0 - e->textArea->firstColumn, e->textArea->cursor->position.y});
                        break;
                    case SHOW_LINES:
                        e->textArea->numbersDisplayed = true;
                        e->textArea->changes = true;
                        e->textArea->bkChanges = true;
                        break;
                    case HIDE_LINES:
                        e->textArea->numbersDisplayed = false;
                        e->textArea->changes = true;
                        e->textArea->bkChanges = true;
                        break;
                    case SWITCH_ORIENTATION_V:
                        switchOrientation(e, VERTICAL);
                        break;
                    case SWITCH_ORIENTATION_H:
                        switchOrientation(e, HORIZONTAL);
                        break;
                    }

                    deleteButtonsList(currentButton->subMenu);
                    currentButton->subMenu = NULL;
                    currentButton->pressed = false;
                    e->root->changes = true;
                    e->textArea->changes = true;
                    e->textArea->bkChanges = true;
                    currentButton->changes = true;
                    subMenuButton->changes = true;
                    ma->changes = true;
                    clearmouseclick(WM_LBUTTONUP);
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
            case OPTIONS:
                showOptionsSubMenu(currentButton, ma);
                break;
            }

            currentButton->changes = true;
            ma->changes = true;
            clearmouseclick(WM_LBUTTONUP);
            return true;
        }
    }
    clearmouseclick(WM_LBUTTONUP);
    return false;
}

void handleClickChangeTextArea(Editor *e, int x, int y)
{
    if(cursorInTextSpace(e, x, y))
    {
        e->clipboard->selectionMade = false;
        changeFocusedTextArea(e->root, x, y);
    }
}

void changeFocusedTextArea(TextAreaNodeTree *root, int x, int y)
{
    if(root->type == ORIENTATION)
    {
        for(TextAreaNodeTree *current = root->tantl->first; current != NULL; current = current->next)
        {
            changeFocusedTextArea(current, x, y);
        }

    }
    else if(root->type == LEAF_NODE)
    {
        if(cursorInArea(root->ta, x, y))
        {
            // Change border old focused
            setcolor(convertToBGIColor(TEXTAREA_MARGINS_NORMAL));
            drawBorderTextArea(root->e->textArea);

            drawCursorLine(root->e->textArea, true);
            root->e->textArea->cursor->visibleState = false;

            root->e->textArea = root->ta;
            setcolor(convertToBGIColor(TEXTAREA_MARGINS_FOCUS));
            drawBorderTextArea(root->e->textArea);

            root->e->menuArea->fileStateChanged = true;
            for(Button *b=root->e->menuArea->buttonsList->first; b != NULL; b = b->next)
            {
                b->changes = true;
            }
            root->e->menuArea->bkChanges = true;
            root->e->menuArea->changes = true;
        }
    }
}

bool cursorInArea(TextArea *ta, int x, int y)
{
    return ta->topLeftWindow.x < x && x < ta->bottomRightWindow.x && ta->topLeftWindow.y < y && y < ta->bottomRightWindow.y;
}

bool cursorInTextSpace(Editor *e, int x, int y)
{
    return e->topLeftTextArea.x < x && x < e->bottomRightTextArea.x && e->topLeftTextArea.y < y && y < e->bottomRightTextArea.y;
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
            case OPTIONS:
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
                    e->root->changes = true;
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

Cursor *initCursor()
{
    Cursor* c = new Cursor;
    c->lastBlip = time(0);
    c->visibleState = true;
    c->position = {0,0};
    c->positionInNode = 0;

    return c;
}

void blipCursor(TextArea *ta)
{
    Button *btn = ta->e->menuArea->buttonsList->first;
    while(btn!=NULL)
    {
        if(btn->pressed)
            return;
        btn = btn->next;
    }
    unsigned int newTime = time(0);
    if(newTime-ta->cursor->lastBlip>0)
    {
        if(ta->cursor->visibleState)
        {
            drawCursorLine(ta);
            ta->cursor->visibleState = false;
        }
        else
        {
            drawCursorLine(ta,true);
            ta->cursor->visibleState = true;
        }
        ta->cursor->lastBlip = newTime;
    }
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

    ta->topLeft = {topLeft.x + CHAR_WIDTH/4, topLeft.y+ CHAR_HEIGHT/4};
    ta->bottomRight = {bottomRight.x, bottomRight.y};


    ta->cursor = initCursor();
    ta->firstLine = 0;
    ta->firstColumn = 0;
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
    ta->firstColumn = 0;
    ta->bkChanges = true;
    ta->numbersDisplayed = true;

    ta->topLeftWindow = topLeft;
    ta->bottomRightWindow = bottomRight;

    ta->topLeft = {topLeft.x + CHAR_WIDTH/4, topLeft.y+ CHAR_HEIGHT/4};
    ta->bottomRight = bottomRight;

    ta->pieceTable = initPieceTable();

    ta->maxLines = abs(ta->bottomRight.y - ta->topLeft.y) / CHAR_HEIGHT;
    ta->maxCharLine = abs(ta->bottomRight.x - ta->topLeft.x) / CHAR_WIDTH;

    ta->cursor = initCursor();
    drawCursorLine(ta);
    ta->cursor->pieceTableNode = ta->pieceTable->nodesList->first;
    openFile(ta, fileName);

    return ta;
}

void drawCursorLine(TextArea *ta, bool background)
{
    if(ta != ta->e->textArea) return;
    if(background==true)
        setcolor(convertToBGIColor(TEXTAREA_BK_NORMAL));
    else
        setcolor(convertToBGIColor(TEXTAREA_FONT_NORMAL));
    int x = ta->cursor->position.x*CHAR_WIDTH + ta->topLeft.x;
    int y = ta->cursor->position.y*CHAR_HEIGHT + ta->topLeft.y;
    line(x-1,y,x-1,y+CHAR_HEIGHT-1);
}

void handleScroll(TextArea *ta)
{
    ta->changes = false;
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
        ta->bkChanges = true;
    }

    if(ta->cursor->position.y>=ta->maxLines)
    {
        ta->firstLine += ta->cursor->position.y - ta->maxLines + 1;
        ta->cursor->position.y = ta->maxLines-1;
        ta->changes = true;
        ta->bkChanges = true;
    }
    if(ta->changes)
        drawArea(ta);
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
        if(ptn==NULL)
            ptn = ta->pieceTable->nodesList->last;
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
        handleScroll(ta);
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
        handleScroll(ta);
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
        handleScroll(ta);
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
        handleScroll(ta);
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
    {
        ta->bkChanges = true;
        c->pieceTableNode->numberNewLines--;
        ta->pieceTable->numberOfLines--;
    }

    if(c->positionInNode==c->pieceTableNode->length-1)
    {
        c->pieceTableNode->length--;
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
        updateCursorPosition(ta);
        handleScroll(ta);
        return;
    }

    if(c->positionInNode==0)
    {
        c->pieceTableNode->start++;
        c->pieceTableNode->length--;
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
        updateCursorPosition(ta);
        handleScroll(ta);
        return;
    }

    {
        PieceTableNode *rightSide = initPieceTableNode(c->pieceTableNode->buffer,c->pieceTableNode->start+c->positionInNode+1,c->pieceTableNode->length-c->positionInNode-1,0);
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
        handleScroll(ta);
        return;
    }
}

Clipboard* initClipboard()
{
    Clipboard *newC = new Clipboard;

    newC->selectionMade = false;
    newC->start = new Cursor;
    newC->start->pieceTableNode = NULL;
    newC->finish = new Cursor;
    newC->start->pieceTableNode = NULL;

    newC->pieceTable = initPieceTable();
    return newC;
}

void showSelection(Clipboard *c, TextArea *ta)
{
    if(c->selectionMade==false)
        return;
    if(c->start->position.y==c->finish->position.y && c->finish->position.x==c->start->position.x-1)
        return;
    if(ta->pieceTable->nodesList->length == 1 && ta->pieceTable->nodesList->first->length == 0)
        return;

    setbkcolor(convertToBGIColor(TEXTAREA_BK_NORMAL));
    setcolor(convertToBGIColor(TEXTAREA_SELECT_BRACKET));
    Cursor A, B;

    if(c->start->position.y>c->finish->position.y || (c->start->position.y==c->finish->position.y && c->start->position.x>c->finish->position.x))
    {
        A.position = c->finish->position;
        B.position = c->start->position;
    }
    else
    {
        A.position = c->start->position;
        B.position = c->finish->position;
    }

    if(c->start->position.y==c->finish->position.y &&  c->finish->position.x<c->start->position.x)
    {
        A.position.x++;
        B.position.x--;
    }

    if(A.position.x>0)
        outtextxy(ta->topLeft.x+(A.position.x-1)*CHAR_WIDTH,ta->topLeft.y+A.position.y*CHAR_HEIGHT,"{");
    else
        line(ta->topLeft.x+A.position.x*CHAR_WIDTH,ta->topLeft.y+A.position.y*CHAR_HEIGHT,ta->topLeft.x+A.position.x*CHAR_WIDTH,ta->topLeft.y+(A.position.y+1)*CHAR_HEIGHT-1);

    if(B.position.x<ta->maxCharLine)
        outtextxy(ta->topLeft.x+(B.position.x+1)*CHAR_WIDTH,ta->topLeft.y+B.position.y*CHAR_HEIGHT,"}");
    else
        line(ta->topLeft.x+B.position.x*CHAR_WIDTH,ta->topLeft.y+B.position.y*CHAR_HEIGHT,ta->topLeft.x+B.position.x*CHAR_WIDTH,ta->topLeft.y+(B.position.y+1)*CHAR_HEIGHT-1);
}

void hideSelection(Clipboard *c, TextArea *ta)
{
    if(c->selectionMade==false)
        return;

    drawLines(ta,ta->topLeft.y+c->start->position.y*CHAR_HEIGHT,ta->topLeft.y+(c->start->position.y+1)*CHAR_HEIGHT);
    if(c->start->position.y!=c->finish->position.y)
        drawLines(ta,ta->topLeft.y+c->finish->position.y*CHAR_HEIGHT,ta->topLeft.y+(c->finish->position.y+1)*CHAR_HEIGHT);
}

void validateSelection(Clipboard *c)
{
    if(c->selectionMade==false)
        return;

    if(c->start->position.y>c->finish->position.y || (c->start->position.y==c->finish->position.y && c->start->position.x>c->finish->position.x))
    {
        Cursor *aux = c->start;
        c->start = c->finish;
        c->finish = aux;
    }
}

void selectAll(Clipboard *c, TextArea *ta)
{
    if(ta->pieceTable->nodesList->length==1 && ta->pieceTable->nodesList->first->length==0)
        return;

    c->selectionMade = true;
    c->start->pieceTableNode = ta->pieceTable->nodesList->first;
    c->start->positionInNode = 0;
    c->start->position = {0,0};

    c->finish->pieceTableNode = ta->pieceTable->nodesList->last;
    c->finish->positionInNode = c->finish->pieceTableNode->length-1;

    Cursor* prevCursor = new Cursor;
    prevCursor = ta->cursor;
    ta->cursor = c->finish;
    updateCursorPosition(ta);
    c->finish = ta->cursor;
    ta->cursor = prevCursor;

    showSelection(c,ta);
}

void emptyClipboard(Clipboard *c)
{
    while(c->pieceTable->nodesList->length!=0)
        removeLastPieceTableNode(c->pieceTable->nodesList);
}

void copyToClipboard(Clipboard *c, TextArea *ta)
{
    if(c->selectionMade==false || c->finish->positionInNode==-1)
        return;

    if(c->start->pieceTableNode==ta->pieceTable->nodesList->first && c->start->pieceTableNode->length==0)
    {
        c->start->pieceTableNode = c->start->pieceTableNode->next;
        c->start->positionInNode = 0;
    }


    hideSelection(c,ta);
    c->selectionMade = false;

    emptyClipboard(c);

    PieceTableNode *sourcePTN = c->start->pieceTableNode;
    PieceTableNode *destPTN;
    unsigned int numberNewLines;
    unsigned int i;

    if(c->start->pieceTableNode==c->finish->pieceTableNode)
    {
        if(c->finish->positionInNode!=c->finish->pieceTableNode->length-1)
            c->finish->positionInNode--;

        numberNewLines = 0;
        for(i=c->start->positionInNode; i<=c->finish->positionInNode; i++)
            if(sourcePTN->buffer->text[sourcePTN->start+i]=='\n')
                numberNewLines++;
        destPTN = initPieceTableNode(sourcePTN->buffer,sourcePTN->start+c->start->positionInNode,c->finish->positionInNode-c->start->positionInNode+1,numberNewLines);
        addPieceTableNode(c->pieceTable->nodesList,destPTN);
        c->pieceTable->numberOfLines += numberNewLines;
        return;
    }

    if(c->start->positionInNode!=0)
    {
        numberNewLines = 0;
        for(i=c->start->positionInNode; i<c->start->pieceTableNode->length; i++)
            if(sourcePTN->buffer->text[sourcePTN->start+i]=='\n')
                numberNewLines++;
        destPTN = initPieceTableNode(sourcePTN->buffer,sourcePTN->start+c->start->positionInNode,sourcePTN->length-c->start->positionInNode,numberNewLines);
        addPieceTableNode(c->pieceTable->nodesList,destPTN);
        c->pieceTable->numberOfLines += numberNewLines;
        sourcePTN = sourcePTN->next;
    }

    while(sourcePTN!=c->finish->pieceTableNode)
    {
        destPTN = initPieceTableNode(sourcePTN->buffer,sourcePTN->start,sourcePTN->length,sourcePTN->numberNewLines);
        addPieceTableNode(c->pieceTable->nodesList,destPTN);
        c->pieceTable->numberOfLines += destPTN->numberNewLines;
        sourcePTN = sourcePTN->next;
    }

    if(c->finish->pieceTableNode==ta->pieceTable->nodesList->last && c->finish->positionInNode==c->finish->pieceTableNode->length-1)
    {
        destPTN = initPieceTableNode(sourcePTN->buffer,sourcePTN->start,sourcePTN->length,sourcePTN->numberNewLines);
        addPieceTableNode(c->pieceTable->nodesList,destPTN);
        c->pieceTable->numberOfLines += destPTN->numberNewLines;
        return;
    }

    numberNewLines = 0;
    for(i=0; i<=c->finish->positionInNode; i++)
        if(sourcePTN->buffer->text[sourcePTN->start+i]=='\n')
            numberNewLines++;
    destPTN = initPieceTableNode(sourcePTN->buffer,sourcePTN->start,c->finish->positionInNode,numberNewLines);
    addPieceTableNode(c->pieceTable->nodesList,destPTN);
    c->pieceTable->numberOfLines += numberNewLines;
    sourcePTN = sourcePTN->next;
}

void deleteSelection(Clipboard *c, TextArea *ta)
{
    if(c->selectionMade==false || c->start->pieceTableNode==NULL)
        return;

    ta->e->menuArea->fileStateChanged = true;
    ta->e->menuArea->changes = true;
    ta->savedChanges = false;

    hideSelection(c,ta);
    c->selectionMade = false;
    unsigned int i;
    PieceTableNode *currPTN = c->start->pieceTableNode, *aux;

    if(currPTN->prev!=NULL)
    {
        ta->cursor->pieceTableNode = currPTN->prev;
        ta->cursor->positionInNode = ta->cursor->pieceTableNode->length;
    }

    if(currPTN==c->finish->pieceTableNode || c->start->positionInNode!=0 || (c->start->pieceTableNode==ta->pieceTable->nodesList->first && c->start->positionInNode==0))
    {
        ta->cursor->pieceTableNode = currPTN;
        ta->cursor->positionInNode = c->start->positionInNode;

        PieceTableNode *rightSide = initPieceTableNode(currPTN->buffer,currPTN->start+c->start->positionInNode,currPTN->length-c->start->positionInNode,0);
        for(i=0; i<rightSide->length; i++)
            if(rightSide->buffer->text[rightSide->start+i]=='\n')
                rightSide->numberNewLines++;
        currPTN->numberNewLines -= rightSide->numberNewLines;
        currPTN->length = c->start->positionInNode;

        if(currPTN->next!=NULL)
            currPTN->next->prev = rightSide;
        else
            ta->pieceTable->nodesList->last = rightSide;
        rightSide->next = currPTN->next;
        rightSide->prev = currPTN;
        currPTN->next = rightSide;

        if(c->start->pieceTableNode==c->finish->pieceTableNode)
        {
            c->finish->pieceTableNode = rightSide;
            c->finish->positionInNode -= currPTN->length;
        }
        ta->pieceTable->nodesList->length++;
        currPTN = rightSide;
    }


    while(currPTN!=c->finish->pieceTableNode)
    {
        if(currPTN->next!=NULL)
            currPTN->next->prev = currPTN->prev;
        currPTN->prev->next = currPTN->next;
        aux = currPTN;
        currPTN = currPTN->next;
        ta->pieceTable->nodesList->length--;
        ta->pieceTable->numberOfLines -= aux->numberNewLines;
        delete aux;
    }

    if(currPTN==ta->pieceTable->nodesList->last && c->finish->positionInNode==c->finish->pieceTableNode->length-1)
    {
        ta->pieceTable->nodesList->length--;
        ta->pieceTable->numberOfLines -= currPTN->numberNewLines;
        ta->pieceTable->nodesList->last = currPTN->prev;
        ta->pieceTable->nodesList->last->next = NULL;
        delete currPTN;
    }
    else
    {
        for(i=0; i<=c->finish->positionInNode; i++)
            if(currPTN->buffer->text[currPTN->start+i]=='\n')
            {
                currPTN->numberNewLines--;
                ta->pieceTable->numberOfLines--;
            }
        currPTN->length -= i;
        currPTN->start += i;
    }

    updateCursorPosition(ta);
    handleScroll(ta);

    ta->changes = true;
    ta->bkChanges = true;
}

void pasteFromClipboard(Clipboard *c, TextArea *ta)
{
    if(c->pieceTable->nodesList->length==0)
        return;

    ta->e->menuArea->fileStateChanged = true;
    ta->e->menuArea->changes = true;
    ta->savedChanges = false;

    hideSelection(c,ta);
    c->selectionMade = false;

    while(ta->pieceTable->nodesList->first->length==0 && ta->pieceTable->nodesList->first->next!=NULL)
    {
        ta->pieceTable->nodesList->first = ta->pieceTable->nodesList->first->next;
        ta->pieceTable->nodesList->length--;
    }

    if(ta->cursor->positionInNode==ta->cursor->pieceTableNode->length && ta->cursor->pieceTableNode->next!=NULL)
    {
        ta->cursor->pieceTableNode = ta->cursor->pieceTableNode->next;
        ta->cursor->positionInNode = 0;
    }

    PieceTableNodesList *pastedText = initPieceTableNodesList();
    PieceTableNode *sourcePTN = c->pieceTable->nodesList->first, *destPTN;

    while(sourcePTN!=NULL)
    {
        if(sourcePTN->length==0)
        {
            sourcePTN = sourcePTN->next;
            continue;
        }
        destPTN = initPieceTableNode(sourcePTN->buffer,sourcePTN->start,sourcePTN->length,sourcePTN->numberNewLines);
        addPieceTableNode(pastedText,destPTN);
        ta->pieceTable->numberOfLines += destPTN->numberNewLines;
        sourcePTN = sourcePTN->next;
    }

    if(ta->pieceTable->nodesList->length==1 && ta->pieceTable->nodesList->first->length==0)
    {
        ta->pieceTable->nodesList = pastedText;
        ta->cursor->pieceTableNode = pastedText->last;
        ta->cursor->positionInNode = pastedText->last->length;

        updateCursorPosition(ta);
        handleScroll(ta);

        return;
    }

    if(ta->cursor->pieceTableNode==ta->pieceTable->nodesList->first && ta->cursor->positionInNode==0)
    {
        ta->pieceTable->nodesList->first->prev = pastedText->last;
        pastedText->last->next = ta->pieceTable->nodesList->first;
        ta->pieceTable->nodesList->first = pastedText->first;
        ta->pieceTable->nodesList->length += pastedText->length;

        ta->cursor->pieceTableNode = ta->pieceTable->nodesList->last;
        ta->cursor->positionInNode = ta->cursor->pieceTableNode->length;
        updateCursorPosition(ta);
        handleScroll(ta);

        delete pastedText;
        return;
    }

    if(ta->cursor->pieceTableNode==ta->pieceTable->nodesList->last && ta->cursor->positionInNode==ta->pieceTable->nodesList->last->length)
    {
        ta->pieceTable->nodesList->last->next = pastedText->first;
        pastedText->first->prev = ta->pieceTable->nodesList->last;
        ta->pieceTable->nodesList->last = pastedText->last;
        ta->pieceTable->nodesList->length += pastedText->length;

        ta->cursor->pieceTableNode = ta->pieceTable->nodesList->last;
        ta->cursor->positionInNode = ta->cursor->pieceTableNode->length;
        updateCursorPosition(ta);
        handleScroll(ta);

        delete pastedText;
        return;
    }

    if(ta->cursor->positionInNode>0)
    {
        PieceTableNode *newPTN = initPieceTableNode(ta->cursor->pieceTableNode->buffer,ta->cursor->pieceTableNode->start + ta->cursor->positionInNode, ta->cursor->pieceTableNode->length - ta->cursor->positionInNode,0);
        for(unsigned int i=0; i<newPTN->length; i++)
            if(newPTN->buffer->text[newPTN->start+i]=='\n')
                newPTN->numberNewLines++;
        ta->cursor->pieceTableNode->numberNewLines -= newPTN->numberNewLines;
        ta->cursor->pieceTableNode->length -= newPTN->length;
        ta->pieceTable->nodesList->length++;

        if(ta->cursor->pieceTableNode->next!=NULL)
            ta->cursor->pieceTableNode->next->prev = newPTN;
        else
            ta->pieceTable->nodesList->last = newPTN;

        newPTN->next = ta->cursor->pieceTableNode->next;
        ta->cursor->pieceTableNode->next = newPTN;
        newPTN->prev = ta->cursor->pieceTableNode;

        ta->cursor->pieceTableNode = newPTN;
        ta->cursor->positionInNode = 0;
    }

    ta->cursor->pieceTableNode->prev->next = pastedText->first;
    pastedText->first->prev = ta->cursor->pieceTableNode->prev;
    pastedText->last->next = ta->cursor->pieceTableNode;
    ta->cursor->pieceTableNode->prev = pastedText->last;
    ta->pieceTable->nodesList->length += pastedText->length;

    updateCursorPosition(ta);
    handleScroll(ta);
    delete pastedText;
}

void cutSelection(Clipboard *c, TextArea *ta)
{
    if(c->selectionMade==false)
        return;
    copyToClipboard(c,ta);
    c->selectionMade = true;
    deleteSelection(c,ta);
}

Editor* initEditor()
{
    initwindow(MAX_WIDTH,MAX_HEIGHT,"Notepad Improved");
    settextstyle(0, HORIZ_DIR, 2);

    setbkcolor(convertToBGIColor(TEXTAREA_BK_NORMAL));
    setcolor(convertToBGIColor(TEXTAREA_FONT_NORMAL));
    cleardevice();

    Editor *e = new Editor;
    e->running = true;

    Point topLeft, bottomRight;

    topLeft= {0, 0};
    e->menuArea = initMenuArea(topLeft, e);

    topLeft= {0,0};
    bottomRight = {MAX_WIDTH,MAX_HEIGHT};

    topLeft= {0, e->menuArea->bottomRight.y};
    bottomRight = {MAX_WIDTH - 1,MAX_HEIGHT - 1};


    e->topLeftTextArea = topLeft;
    e->bottomRightTextArea = bottomRight;

    // e->textArea = initTextArea(e, topLeft, bottomRight, "textText.txt");
    e->textArea = initTextArea(e, topLeft, bottomRight);
    e->root = initTextAreaNodeTree(e, HORIZONTAL);

    TextAreaNodeTree* tan = initTextAreaNodeTree(e, e->textArea);
    addNodeToTANTL(e->root->tantl, 0, tan);

    e->clipboard = initClipboard();

    e->modalOpen = false;
    e->m1 = NULL;
    e->m2 = NULL;

    return e;
}

void calculateDimensionsForTextAreas(TextAreaNodeTree *root)
{
    if(root->e->root == root)
    {
        root->topLeft = root->e->topLeftTextArea;
        root->bottomRight = root->e->bottomRightTextArea;
    }

    if(root->type == ORIENTATION)
    {
        Point topLeft = root->topLeft;
        Point bottomRight;
        int modifier;

        switch (root->orientation)
        {
        case HORIZONTAL:
            modifier = (root->bottomRight.x - root->topLeft.x) / (int)root->tantl->length;
            bottomRight = {root->topLeft.x, root->bottomRight.y};


            for(TextAreaNodeTree *current = root->tantl->first; current != NULL; current = current->next)
            {
                if(current != root->tantl->first) topLeft.x += 1;
                current->topLeft = topLeft;
                bottomRight.x = topLeft.x + modifier;
                if(current == root->tantl->last) bottomRight.x -= (root->tantl->length - 1);
                current->bottomRight = bottomRight;
                topLeft.x = bottomRight.x;

                calculateDimensionsForTextAreas(current);
            }
            break;
        case VERTICAL:
            modifier = (root->bottomRight.y - root->topLeft.y) / (int)root->tantl->length;
            bottomRight = {root->bottomRight.x, root->topLeft.y};

            for(TextAreaNodeTree *current = root->tantl->first; current != NULL; current = current->next)
            {
                if(current != root->tantl->first) topLeft.y += 1;
                current->topLeft = topLeft;
                bottomRight.y = topLeft.y + modifier;
                if(current == root->tantl->last) bottomRight.y -= (root->tantl->length - 1);
                current->bottomRight = bottomRight;
                topLeft.y = bottomRight.y;

                calculateDimensionsForTextAreas(current);
            }
            break;
        }

        setcolor(convertToBGIColor(TEXTAREA_MARGINS_NORMAL));
        line(root->topLeft.x, root->topLeft.y, root->bottomRight.x, root->topLeft.y);
        line(root->topLeft.x, root->topLeft.y, root->topLeft.x, root->bottomRight.y);
        line(root->bottomRight.x, root->bottomRight.y, root->bottomRight.x, root->topLeft.y);
        line(root->bottomRight.x, root->bottomRight.y, root->topLeft.x, root->bottomRight.y);
    }
    else if(root->type == LEAF_NODE)
    {
        root->ta->topLeftWindow = root->topLeft;
        root->ta->bottomRightWindow = root->bottomRight;

        root->ta->changes = true;
        root->ta->bkChanges = true;

        drawArea(root->ta);

        if(root->ta == root->e->textArea)
        {
            setcolor(convertToBGIColor(TEXTAREA_MARGINS_FOCUS));
        }
        else
        {
            setcolor(convertToBGIColor(TEXTAREA_MARGINS_NORMAL));
        }

        drawBorderTextArea(root->ta);
    }
}

void drawBorderTextArea(TextArea *ta)
{
    line(ta->topLeftWindow.x, ta->topLeftWindow.y, ta->bottomRightWindow.x, ta->topLeftWindow.y);
    line(ta->topLeftWindow.x, ta->topLeftWindow.y, ta->topLeftWindow.x, ta->bottomRightWindow.y);
    line(ta->bottomRightWindow.x, ta->bottomRightWindow.y, ta->bottomRightWindow.x, ta->topLeftWindow.y);
    line(ta->bottomRightWindow.x, ta->bottomRightWindow.y, ta->topLeftWindow.x, ta->bottomRightWindow.y);
}

TextAreaNodeTree* initTextAreaNodeTree(Editor *e, Orientation orientation)
{
    TextAreaNodeTree *node = new TextAreaNodeTree;
    node->changes = true;
    node->e = e;
    node->next = NULL;
    node->prev = NULL;
    node->parentList = NULL;
    node->tantl = initTextAreaNodeTreeList(e);
    node->tantl->parent = node;
    node->orientation = orientation;
    node->ta = NULL;
    node->type = ORIENTATION;

    return node;
}

TextAreaNodeTree* initTextAreaNodeTree(Editor *e, TextArea *ta)
{
    TextAreaNodeTree *node = new TextAreaNodeTree;
    node->changes = true;
    node->e = e;
    node->next = NULL;
    node->prev = NULL;
    node->parentList = NULL;
    node->tantl = NULL;

    node->ta = ta;
    node->type = LEAF_NODE;

    return node;
}

TextAreaNodeTreeList* initTextAreaNodeTreeList(Editor *e)
{
    TextAreaNodeTreeList *tantl = new TextAreaNodeTreeList;
    tantl->e = e;
    tantl->length = 0;
    tantl->first = NULL;
    tantl->last = NULL;
    tantl->parent = NULL;

    return tantl;
}

// If node is not in the list will return the length of the list
int getNodePositionInTANTL(TextAreaNodeTreeList *tantl, TextAreaNodeTree *node)
{
    int res = 0;
    for(TextAreaNodeTree *current = tantl->first; current != NULL; current = current->next)
    {
        if(current == node) break;
        res++;
    }
    return res;
}

void addNodeToTANTL(TextAreaNodeTreeList *tantl, int position, TextAreaNodeTree *node)
{
    if(position < 0 || position > (int)tantl->length)
        exit(1);

    switch(node->type)
    {
    case LEAF_NODE:
        node->ta->node = node;
        break;
    }
    node->parentList = tantl;

    if(tantl->length == 0)
    {
        tantl->first = node;
        tantl->last = node;
        tantl->length = 1;
        return;
    }
    if(position == 0)
    {
        node->next = tantl->first;
        tantl->first->prev = node;
        tantl->first = node;
        tantl->length++;
        return;
    }
    if(position == (int)tantl->length)
    {
        node->prev = tantl->last;
        tantl->last->next = node;
        tantl->last = node;
        tantl->length++;
        return;
    }

    TextAreaNodeTree *current = tantl->first;
    for(int i=0; i < position - 1; i++, current = current->next);

    current->next->prev = node;
    node->next = current->next;
    current->next = node;
    node->prev = current;
    tantl->length++;
}

void drawTextAreaTree(TextAreaNodeTree *root)
{
    if(root->changes == false) return;

    calculateDimensionsForTextAreas(root);

    setcolor(convertToBGIColor(TEXTAREA_MARGINS_FOCUS));
    drawBorderTextArea(root->e->textArea);
    root->changes = false;
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
            char *newLineInNode = strchr(ptn->buffer->text + indexOfLine, '\n');
            ptn->buffer->text[endOfDisplayedLine] = aux;

            if(newLineInNode)
            {
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
        }

        if(numberOfCharsFromNode <= spaceRemainedOnScreen && !skippedNode)
        {
            endOfDisplayedLine = indexOfLine + numberOfCharsFromNode;

            char aux = ptn->buffer->text[endOfDisplayedLine];
            ptn->buffer->text[endOfDisplayedLine] = '\0';
            char *newLineInNode = strchr(ptn->buffer->text + indexOfLine, '\n');
            ptn->buffer->text[endOfDisplayedLine] = aux;

            if(newLineInNode)
            {
                numberOfCharsFromNode -= endOfDisplayedLine - (newLineInNode - ptn->buffer->text + 1);
                endOfDisplayedLine = newLineInNode - ptn->buffer->text + 1;
                lineEnded = true;
            }

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

    ta->cursor->lastBlip = time(0);
    ta->cursor->visibleState = true;
    drawCursorLine(ta);
}

void drawLinesNumber(TextArea *ta)
{
    setfillstyle(1, convertToBGIColor(TEXTAREA_BK_NORMAL));
    setbkcolor(convertToBGIColor(TEXTAREA_BK_NORMAL));
    setcolor(convertToBGIColor(TEXTAREA_NUMBERS_COLOR));
    bar(ta->topLeftNumbers.x, ta->topLeftNumbers.y, ta->bottomRightNumbers.x, ta->bottomRightNumbers.y);

    line(ta->bottomRightNumbers.x, ta->topLeftWindow.y + 1, ta->bottomRightNumbers.x, ta->bottomRightNumbers.y);
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

void drawArea(TextArea *ta)
{
    if(ta->changes==false)
        return;

    if(ta->bkChanges)
    {
        ta->bottomRight = ta->bottomRightWindow;

        if(!ta->numbersDisplayed)
        {
            ta->topLeft.x = ta->topLeftWindow.x + CHAR_WIDTH/4;
            ta->topLeft.y = ta->topLeftWindow.y + CHAR_HEIGHT/4 - 1;
            ta->bottomRight = ta->bottomRightWindow;
            ta->maxCharLine = abs(ta->bottomRight.x - ta->topLeft.x - numberOfChar(ta->pieceTable->numberOfLines + 1)) / CHAR_WIDTH;
            ta->maxLines = abs(ta->bottomRight.y - ta->topLeft.y) / CHAR_HEIGHT;

            setfillstyle(1, convertToBGIColor(TEXTAREA_BK_NORMAL));
            bar(ta->topLeftWindow.x + 1, ta->topLeftWindow.y + 1, ta->bottomRightWindow.x, ta->bottomRightWindow.y);
        }
        if(ta->numbersDisplayed)
        {
            setfillstyle(1, convertToBGIColor(TEXTAREA_BK_NORMAL));
            setbkcolor(convertToBGIColor(TEXTAREA_BK_NORMAL));
            setcolor(convertToBGIColor(TEXTAREA_NUMBERS_COLOR));

            ta->topLeft.x = ta->topLeftWindow.x + numberOfChar(ta->pieceTable->numberOfLines + 1) * CHAR_WIDTH + CHAR_WIDTH/2 + 1;
            ta->topLeft.y = ta->topLeftWindow.y + CHAR_HEIGHT/4 - 1;
            ta->topLeftNumbers.x = CHAR_WIDTH/4 + ta->topLeftWindow.x + 1;
            ta->topLeftNumbers.y = ta->topLeft.y - 1;
            ta->bottomRightNumbers.x = ta->topLeftNumbers.x + numberOfChar(ta->pieceTable->numberOfLines + 1) * CHAR_WIDTH + 1;
            ta->bottomRightNumbers.y = ta->bottomRight.y - 1;
            ta->maxCharLine = abs(ta->bottomRight.x - ta->topLeft.x - numberOfChar(ta->pieceTable->numberOfLines + 1)) / CHAR_WIDTH;
            ta->maxLines = abs(ta->bottomRight.y - ta->topLeft.y) / CHAR_HEIGHT;


            setfillstyle(1, convertToBGIColor(TEXTAREA_BK_NORMAL));
            bar(ta->topLeftWindow.x + 1, ta->topLeftWindow.y + 1, ta->bottomRightWindow.x, ta->bottomRightWindow.y);

            drawLinesNumber(ta);
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

                if(newBuffer)
                {
                    ta->pieceTable->buffersList->last->prev->text[ta->pieceTable->buffersList->last->prev->length-1] = '\n';
                    ta->pieceTable->nodesList->last->prev->numberNewLines += 1;
                }
                else
                {
                    ta->pieceTable->buffersList->last->text[ta->pieceTable->buffersList->last->length-1] = '\n';
                    ta->pieceTable->nodesList->last->numberNewLines += 1;
                }
            }
            else
            {
                numberNewLines++;
                unixFile = true;
                if(newBuffer) newBuffer->length++;
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

            lastAddedChar = newBuffer->text[newBuffer->length-1];
            newBuffer->text[newBuffer->length] = '\0';
            readSize = newBuffer->length;

            /*if(newBuffer->length == 1 && newBuffer->text[0] == '\0') {
                emptyPieceTable(ta->pieceTable);
            }*/
            ok = false;
        }
    }
    while(readSize == MAX_LENGTH_BUFFER);

    if(unixFile) ta->unixFile = true;
    //Buffer *newBuffer = initBuffer();
    //addBuffer(ta->pieceTable->buffersList, newBuffer);
    //PieceTableNode *newPtn = initPieceTableNode(newBuffer, 0, 0, 0);
    //addPieceTableNode(ta->pieceTable->nodesList, newPtn);

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
    drawTextAreaTree(e->root);
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
    else
        blipCursor(e->textArea);
}

void stopEditor(Editor *e)
{
    e->running = false;
    closegraph();
    // TODO: Delete data from memory
}

Modal1* initModal1(Editor *e, char *title, char *description, ButtonType buttonType)
{
    e->modalOpen = true;

    Modal1 *m1 = new Modal1;
    e->m1 = m1;
    m1->changes = true;
    m1->bkChanges = true;
    m1->buttonType = buttonType;

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
                switch (m1->buttonType)
                {
                case STOP_EDITOR:
                    m1->e->running = false;
                    break;
                }
                break;
            }

            m1->e->root->changes = true;
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
        if(strlen(input->text)>=(input->bottomRight.x-input->topLeft.x-2*(INPUT_MODAL2_PADDING+INPUT_MODAL2_MARGIN_SIZE)-INPUT_MODAL2_MARGIN_SIZE/2)/CHAR_WIDTH)
            outtextxy(input->topLeft.x + INPUT_MODAL2_MARGIN_SIZE + INPUT_MODAL2_PADDING, input->topLeft.y + INPUT_MODAL2_MARGIN_SIZE + INPUT_MODAL2_PADDING, input->text + strlen(input->text) - ((input->bottomRight.x-input->topLeft.x)/CHAR_WIDTH)+2);
        else
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
        if(strlen(input->text)>=(input->bottomRight.x-input->topLeft.x-2*(INPUT_MODAL2_PADDING+INPUT_MODAL2_MARGIN_SIZE)-INPUT_MODAL2_MARGIN_SIZE/2)/CHAR_WIDTH)
            outtextxy(input->topLeft.x + INPUT_MODAL2_MARGIN_SIZE + INPUT_MODAL2_PADDING, input->topLeft.y + INPUT_MODAL2_MARGIN_SIZE + INPUT_MODAL2_PADDING, input->text + strlen(input->text) - ((input->bottomRight.x-input->topLeft.x)/CHAR_WIDTH)+2);
        else
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
    if(strlen(input->text)<=(input->bottomRight.x-input->topLeft.x-2*(INPUT_MODAL2_PADDING+INPUT_MODAL2_MARGIN_SIZE)-INPUT_MODAL2_MARGIN_SIZE/2)/CHAR_WIDTH)
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
    if(strlen(input->text)<(input->bottomRight.x-input->topLeft.x-2*(INPUT_MODAL2_PADDING+INPUT_MODAL2_MARGIN_SIZE)-INPUT_MODAL2_MARGIN_SIZE/2)/CHAR_WIDTH)
        input->cursor->position.x -= CHAR_WIDTH;
    input->cursor->state = true;
    input->cursor->lastUpdate = time(0);
    input->changes = true;
    input->modal->changes = true;
}

Modal2* initModal2(Editor *e, char *title, char *description, char *buttonNameYes, char *buttonNameNo, ButtonType buttonType)
{
    e->modalOpen = true;

    Modal2 *m2 = new Modal2;
    e->m2 = m2;
    m2->error = false;
    m2->errorMessageChanges = false;
    m2->buttonType = buttonType;

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

    m2->bl = initButtonsList({(MAX_WIDTH + MODAL2_WIDTH) / 2 - MODAL2_PADDING - 4*PADDING_SIDES_MODAL2_BTN - CHAR_WIDTH * std::max((int)strlen(buttonsNames[1]),MODAL2_CHARS_BUTTON) - 2*CHAR_WIDTH - CHAR_WIDTH * std::max((int)strlen(buttonsNames[0]),MODAL2_CHARS_BUTTON),
                              m2->bottomRight.y - MODAL2_PADDING - CHAR_HEIGHT - 2*PADDING_TOP_BOTTOM_MODAL2_BTN},
                             buttonsNames, types, 2, styles, MODAL2_BL);
    m2->iM = initInputModal2({m2->topLeft.x + MODAL2_PADDING, m2->bottomRight.y - MODAL2_PADDING - 3*CHAR_HEIGHT - 2*PADDING_TOP_BOTTOM_MODAL2_BTN - 2*INPUT_MODAL2_PADDING - 2*INPUT_MODAL2_MARGIN_SIZE},
    {m2->bottomRight.x - MODAL2_PADDING, m2->bottomRight.y - MODAL2_PADDING - 2*CHAR_HEIGHT - 2*PADDING_TOP_BOTTOM_MODAL2_BTN}, m2);

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
                if(strlen(m2->iM->text) == 0)
                {
                    setErrorMessageModal2(m2, "The input can't be empty!");
                    return;
                }

                switch(m2->buttonType)
                {
                case SAVE_AS_FILE:
                case SAVE_FILE:
                    error = saveFile(m2->e->textArea, m2->iM->text);
                    break;
                case OPEN_FILE:
                    error = openFile(m2->e->textArea, m2->iM->text);
                    break;
                case GO_TO_LINE:
                    if(atoi(m2->iM->text)!=0)
                        getCursorPositionInPiecetable(m2->e->textArea, {-m2->e->textArea->firstColumn, atoi(m2->iM->text) - 1 - m2->e->textArea->firstLine});
                    else
                        getCursorPositionInPiecetable(m2->e->textArea, {-m2->e->textArea->firstColumn, -m2->e->textArea->firstLine});
                    break;
                case GO_TO_COLUMN:
                    if(atoi(m2->iM->text)!=0)
                        getCursorPositionInPiecetable(m2->e->textArea, {atoi(m2->iM->text) - 1 - m2->e->textArea->firstColumn, m2->e->textArea->cursor->position.y});
                    else
                        getCursorPositionInPiecetable(m2->e->textArea, {-m2->e->textArea->firstColumn, m2->e->textArea->cursor->position.y});
                    break;
                }


                if(error)
                {
                    setErrorMessageModal2(m2, "There was a problem with your input!");
                    return;
                }
                break;
            }

            deleteModal2(m2);
            m2->e->root->changes = true;
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

bool verifyFilesAreSaved(TextAreaNodeTree *root)
{
    bool res = true;
    if(root->type == ORIENTATION)
    {
        for(TextAreaNodeTree *current = root->tantl->first; current != NULL; current = current->next)
        {
            res = res && verifyFilesAreSaved(current);
        }
    }
    else if(root->type == LEAF_NODE)
    {
        return root->ta->savedChanges;
    }

    return res;
}
