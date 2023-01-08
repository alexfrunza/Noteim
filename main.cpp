#include <iostream>
#include <ctime>
#include "editor.h"
#include "color.h"
#include "piecetable.h"

#define ARROW_PRESSED a==0
#define CTRL_A_PRESSED a==1
#define CTRL_C_PRESSED a==3
#define BACKSPACE_PRESSED a==8
#define CTRL_V_PRESSED a==22
#define CTRL_X_PRESSED a==24
#define ESC_PRESSED a==27
#define DELETE_PRESSED a==83
#define ENTER_PRESSED a=='\r'
#define TAB_PRESSED a=='\t'

using namespace std;

bool buttonPressed = false;

void logPieceTableNodes(PieceTable *pt)
{
    PieceTableNodesList *ptnl = pt->nodesList;


    int i;
    printf("\n\n");
    PieceTableNode *ptn = pt->nodesList->first;
    cout<<"NODES LIST: " << pt->nodesList->length << " nodes\n";
    while(ptn!=NULL)
    {
        cout<<"START: "<<ptn->start<<" LENGTH: "<<ptn->length<< " NUMBERNEWLINES: " << ptn->numberNewLines << " ADDRESS: "<<ptn <<'\n';
        for(i=0; i<ptn->length; i++)
            cout << ptn->buffer->text[ptn->start+i];
        ptn = ptn->next;
    }

}

void handleDelete(TextArea *ta)
{
    Cursor *c = ta->cursor;
    int prevNumberOfLines = ta->pieceTable->numberOfLines;
    removeCharFromTextArea(ta);
    if(ta->changes==true)
        drawArea(ta);
    else if(prevNumberOfLines-ta->pieceTable->numberOfLines!=0)
         {
            if(ta->pieceTable->numberOfLines<=ta->maxLines+ta->firstLine)
            {
                if(numberOfChar(ta->pieceTable->numberOfLines)!=numberOfChar(ta->pieceTable->numberOfLines+2))
                    {
                        ta->changes = true;
                        drawArea(ta);
                    }
                else if(ta->numbersDisplayed==true)
                    drawLinesNumber(ta);
            }
                drawLines(ta,ta->topLeft.y+c->position.y*CHAR_HEIGHT,ta->bottomRight.y);
         }
        else
            drawLines(ta,ta->topLeft.y+c->position.y*CHAR_HEIGHT,ta->topLeft.y+(c->position.y+1)*CHAR_HEIGHT);
}

void handleKeyPress(Editor *e)
{
    char a = getch();
    if(ESC_PRESSED)
    {
        if(!verifyFilesAreSaved(e->root)) initModal1(e, "Close editor", "There are windows which are not\nsaved. Are you sure\?", STOP_EDITOR);
        else stopEditor(e);
        return;
    }
    if(e->modalOpen)
    {
        if(e->m2 != NULL)
        {
            if(e->m2->iM->state)
            {
                if(e->m2->buttonType == GO_TO_LINE || e->m2->buttonType == GO_TO_COLUMN)
                {
                    if(isNumber(a))
                    {
                        addCharToModal2Input(e->m2->iM, a);
                    } else
                    {
                        setErrorMessageModal2(e->m2, "You can insert only numbers!");
                    }
                }
                else
                {
                    if(isDisplayedChar(a))
                    {
                        addCharToModal2Input(e->m2->iM, a);
                    }
                }
                if(BACKSPACE_PRESSED)
                {
                    deleteCharFromModal2Input(e->m2->iM);
                }
            }
        }
    }
    else
    {
        if(CTRL_A_PRESSED)
            selectAll(e->clipboard,e->textArea);

        if(CTRL_C_PRESSED)
            copyToClipboard(e->clipboard,e->textArea);

        if(CTRL_V_PRESSED)
        {
            if(e->clipboard->selectionMade==true)
                deleteSelection(e->clipboard,e->textArea);
            pasteFromClipboard(e->clipboard,e->textArea);
            e->textArea->changes = e->textArea->bkChanges = true;
            drawArea(e->textArea);
        }

        if(CTRL_X_PRESSED)
        {
            cutSelection(e->clipboard,e->textArea);
            drawArea(e->textArea);
        }

        if(ARROW_PRESSED)
        {
            a = getch();
            if(DELETE_PRESSED) // Both Delete and ArrowKeys send ASCII: 0 then some value
            {
                e->clipboard->selectionMade = false;
                if(e->textArea->cursor->positionInNode<e->textArea->cursor->pieceTableNode->length)
                {
                    e->textArea->cursor->positionInNode++;
                    handleDelete(e->textArea);
                }
                else if(e->textArea->cursor->pieceTableNode->next!=NULL)
                {
                    e->textArea->cursor->pieceTableNode = e->textArea->cursor->pieceTableNode->next;
                    e->textArea->cursor->positionInNode = 1;
                    handleDelete(e->textArea);
                }
            }
            else
            {
                if(e->clipboard->selectionMade==true)
                    e->clipboard->selectionMade = false;
                moveCursorByArrow(e->textArea,a);
            }
            return;
        }

        drawCursorLine(e->textArea,true);

        if(BACKSPACE_PRESSED)
        {
            if(e->clipboard->selectionMade==true)
                deleteSelection(e->clipboard,e->textArea);
            handleDelete(e->textArea);
            e->textArea->savedChanges = false;
            e->menuArea->fileStateChanged = true;
            e->menuArea->changes = true;
        }

        if(ENTER_PRESSED)
        {
            if(e->clipboard->selectionMade==true)
                deleteSelection(e->clipboard,e->textArea);
            addCharToTextArea(e->textArea,'\n');
            if(e->textArea->changes==true)
                drawArea(e->textArea);
            else
                drawLines(e->textArea,e->textArea->topLeft.y+(e->textArea->cursor->position.y-1)*CHAR_HEIGHT,e->textArea->bottomRight.y);
            if(e->textArea->pieceTable->numberOfLines<=e->textArea->maxLines+e->textArea->firstLine)
                if(numberOfChar(e->textArea->pieceTable->numberOfLines)==numberOfChar(e->textArea->pieceTable->numberOfLines+1))
                {
                    if(e->textArea->numbersDisplayed==true)
                        drawLinesNumber(e->textArea);
                }
                else
                {
                    e->textArea->changes = true;
                    drawArea(e->textArea);
                }
            e->textArea->savedChanges = false;
            e->menuArea->fileStateChanged = true;
            e->menuArea->changes = true;
        }

        if(TAB_PRESSED)
        {
            if(e->clipboard->selectionMade==true)
                deleteSelection(e->clipboard,e->textArea);
            bool changedByDeletion = e->textArea->changes;
            addCharToTextArea(e->textArea,' ');
            addCharToTextArea(e->textArea,' ');
            addCharToTextArea(e->textArea,' ');
            addCharToTextArea(e->textArea,' ');
            e->textArea->savedChanges = false;
            e->menuArea->fileStateChanged = true;
            e->menuArea->changes = true;
            e->textArea->changes = e->textArea->changes || changedByDeletion;
            if(e->textArea->changes==true)
                drawArea(e->textArea);
            else
                drawLines(e->textArea,e->textArea->topLeft.y+(e->textArea->cursor->position.y)*CHAR_HEIGHT,e->textArea->topLeft.y+(e->textArea->cursor->position.y+1)*CHAR_HEIGHT);
        }

        if(isDisplayedChar(a))
        {
            if(e->clipboard->selectionMade==true)
                deleteSelection(e->clipboard,e->textArea);
            bool changedByDeletion = e->textArea->changes;
            addCharToTextArea(e->textArea,a);
            e->textArea->changes = e->textArea->changes || changedByDeletion;
            if(e->textArea->changes==true)
                drawArea(e->textArea);
            else
                drawLines(e->textArea,e->textArea->topLeft.y+e->textArea->cursor->position.y*CHAR_HEIGHT,e->textArea->topLeft.y+(e->textArea->cursor->position.y+1)*CHAR_HEIGHT);
            e->textArea->savedChanges = false;
            e->menuArea->fileStateChanged = true;
            e->menuArea->changes = true;
        }
    }
}

void handleMouseClick(Editor *e)
{
    int x, y;

    if(e->clipboard->selectionMade==true)
    {
        hideSelection(e->clipboard,e->textArea);
        e->clipboard->selectionMade = false;
    }

    getmouseclick(WM_LBUTTONDOWN,x,y);

    if(e->modalOpen)
    {
        if(e->m1 != NULL)
        {
            handleClick(e->m1, x, y);
            clearmouseclick(WM_LBUTTONUP);
        }
        if(e->m2 != NULL)
        {
            clearClick(e->m2, x, y);
            handleClick(e->m2, x, y);
            clearmouseclick(WM_LBUTTONUP);
        }
    }
    else
    {
        /// Verify a button is clicked or something from a submenu
        bool pressed = false;
        pressed = handleClick(e, x, y);
        pressed = clearClick(e, x, y) || pressed;
        buttonPressed = pressed;
        ///
        if(pressed)
            clearmouseclick(WM_LBUTTONUP);
        else
            handleClickChangeTextArea(e, x, y);

        if(x>=e->textArea->topLeft.x && x<=e->textArea->bottomRight.x && y>=e->textArea->topLeft.y && y<=e->textArea->bottomRight.y && !pressed)
        {
            x -= e->textArea->topLeft.x;
            y -= e->textArea->topLeft.y;
            Point newCursorPosition = {x/CHAR_WIDTH,y/CHAR_HEIGHT};
            if(x%CHAR_WIDTH>=CHAR_WIDTH/2)
                newCursorPosition.x++;
            moveCursor(e->textArea,newCursorPosition);
            delay(100);
        }

        if(!ismouseclick(WM_LBUTTONUP) && !pressed)
        {
            delete e->clipboard->start;
            delete e->clipboard->finish;
            Cursor *st = new Cursor;
            Cursor *dr = new Cursor;
            st->pieceTableNode = dr->pieceTableNode = e->textArea->cursor->pieceTableNode;
            st->positionInNode = dr->positionInNode = e->textArea->cursor->positionInNode;
            st->position = dr->position = e->textArea->cursor->position;
            dr->position.x--;
            e->clipboard->start = st;
            e->clipboard->finish = dr;
            e->clipboard->selectionMade = true;

            x += e->textArea->topLeft.x;
            y += e->textArea->topLeft.y;

            while(!ismouseclick(WM_LBUTTONUP) && x>=e->textArea->topLeft.x && x<=e->textArea->bottomRight.x && y>=e->textArea->topLeft.y && y<=e->textArea->bottomRight.y)
            {
                hideSelection(e->clipboard,e->textArea);

                x = mousex();
                y = mousey();
                x -= e->textArea->topLeft.x;
                y -= e->textArea->topLeft.y;
                Point newCursorPosition = {x/CHAR_WIDTH,y/CHAR_HEIGHT};
                if(x%CHAR_WIDTH>=CHAR_WIDTH/2)
                    newCursorPosition.x++;
                moveCursor(e->textArea,newCursorPosition);
                x += e->textArea->topLeft.x;
                y += e->textArea->topLeft.y;

                dr->pieceTableNode = e->textArea->cursor->pieceTableNode;
                dr->positionInNode = e->textArea->cursor->positionInNode;
                dr->position = e->textArea->cursor->position;
                if(dr->position.x>0)
                    dr->position.x--;

                showSelection(e->clipboard,e->textArea);
                delay(50);
            }
            while(!ismouseclick(WM_LBUTTONUP))
                delay(50);
        }
        clearmouseclick(WM_LBUTTONUP);
    }
}

void handleMouseHover(Editor *e)
{
    int mx = mousex();
    int my = mousey();

    if(e->modalOpen)
    {
        if(e->m1 != NULL)
        {
            handleHover(e->m1, mx, my);
            clearHover(e->m1, mx, my);
        }
        if(e->m2 != NULL)
        {
            if(time(0) - e->m2->iM->cursor->lastUpdate >= 1)
            {
                changeCursor(e->m2->iM->cursor);
            }
            handleHover(e->m2, mx, my);
            clearHover(e->m2, mx, my);
        }
    }
    else
    {
        handleHover(e->menuArea, mx, my);
        clearHover(e->menuArea, mx, my);
    }
}

int main()
{
    Editor* e = initEditor();
    while(e->running)
    {
        if(buttonPressed && ismouseclick(WM_LBUTTONUP))
        {
            clearmouseclick(WM_LBUTTONUP);
            buttonPressed = false;
        }

        handleMouseHover(e);

        if(ismouseclick(WM_LBUTTONDOWN))
            handleMouseClick(e);

        if(kbhit()) handleKeyPress(e);

        if(e->running)
            drawEditor(e);
        delay(10);
    }
    return 0;
}
