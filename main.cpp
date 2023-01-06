#include <iostream>
#include <ctime>
#include "editor.h"
#include "color.h"
#include "piecetable.h"

#define ARROW_PRESSED a==0
#define ESC_PRESSED a==27
#define BACKSPACE_PRESSED a==8
#define DELETE_PRESSED a==83
#define ENTER_PRESSED a=='\r'
#define TAB_PRESSED a=='\t'

using namespace std;

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
                else
                    drawLinesNumber(ta);
            }
                drawLines(ta,ta->topLeft.y+c->position.y*CHAR_HEIGHT,ta->bottomRight.y);
         }
        else
            drawLines(ta,ta->topLeft.y+c->position.y*CHAR_HEIGHT,ta->topLeft.y+(c->position.y+1)*CHAR_HEIGHT);
}

int main()
{
    Editor* e = initEditor();
    char a;
    int x, y;
    while(e->running)
    {
        Cursor *c = e->textArea->cursor;
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

        if(ismouseclick(WM_LBUTTONDOWN))
        {
            getmouseclick(WM_LBUTTONDOWN,x,y);
            if(e->modalOpen)
            {
                if(e->m1 != NULL)
                {
                    handleClick(e->m1, x, y);
                }
                if(e->m2 != NULL)
                {
                    clearClick(e->m2, x, y);
                    handleClick(e->m2, x, y);
                }
            }
            else
            {
                /// Verify a button is clicked or something from a submenu
                bool pressed = false;
                pressed = handleClick(e, x, y);
                pressed = clearClick(e, x, y) || pressed;
                ///
                if(!pressed) {
                    handleClickChangeTextArea(e, x, y);
                }

                if(x>=e->textArea->topLeft.x && x<=e->textArea->bottomRight.x &&
                        y>=e->textArea->topLeft.y && y<=e->textArea->bottomRight.y && !pressed)
                {
                    x -= e->textArea->topLeft.x;
                    y -= e->textArea->topLeft.y;
                    Point newCursorPosition = {x/CHAR_WIDTH,y/CHAR_HEIGHT};
                    if(x%CHAR_WIDTH>=CHAR_WIDTH/2)
                        newCursorPosition.x++;
                    moveCursor(e->textArea,newCursorPosition);
                    continue;
                }
            }
        }
        if(kbhit())
        {
            a = getch();
            if(ESC_PRESSED)
            {
                stopEditor(e);
                // Maybe pop-up do you want to save the file, if the file isn't saved.
                continue;
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
                        if(a == 8)
                        {
                            deleteCharFromModal2Input(e->m2->iM);
                        }
                    }
                }
            }
            else
            {
                if(a==1)
                    selectAll(e->clipboard,e->textArea);
                if(a==3)
                {
                    copyToClipboard(e->clipboard,e->textArea);
                    logPieceTableNodes(e->clipboard->pieceTable);
                }
                if(ARROW_PRESSED)
                {
                    a = getch();
                    if(DELETE_PRESSED)
                    {
                        if(c->positionInNode<c->pieceTableNode->length)
                        {
                            c->positionInNode++;
                            handleDelete(e->textArea);
                        }
                        else if(c->pieceTableNode->next!=NULL)
                        {
                            c->pieceTableNode = c->pieceTableNode->next;
                            c->positionInNode = 1;
                            handleDelete(e->textArea);
                        }
                    }
                    else
                        moveCursorByArrow(e->textArea,a);
                    continue;
                }
                drawCursorLine(e->textArea,true);
                if(BACKSPACE_PRESSED)
                {
                    handleDelete(e->textArea);
                    e->textArea->savedChanges = false;
                    e->menuArea->fileStateChanged = true;
                    e->menuArea->changes = true;
                }
                if(ENTER_PRESSED)
                {
                    addCharToTextArea(e->textArea,'\n');
                    if(e->textArea->changes==true)
                        drawArea(e->textArea);
                    else
                        drawLines(e->textArea,e->textArea->topLeft.y+(c->position.y-1)*CHAR_HEIGHT,e->textArea->bottomRight.y);
                    if(e->textArea->pieceTable->numberOfLines<=e->textArea->maxLines+e->textArea->firstLine)
                        if(numberOfChar(e->textArea->pieceTable->numberOfLines)==numberOfChar(e->textArea->pieceTable->numberOfLines+1))
                            drawLinesNumber(e->textArea);
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
                    addCharToTextArea(e->textArea,' ');
                    addCharToTextArea(e->textArea,' ');
                    addCharToTextArea(e->textArea,' ');
                    addCharToTextArea(e->textArea,' ');
                    e->textArea->savedChanges = false;
                    e->menuArea->fileStateChanged = true;
                    e->menuArea->changes = true;
                    drawLines(e->textArea,e->textArea->topLeft.y+(c->position.y)*CHAR_HEIGHT,e->textArea->topLeft.y+(c->position.y+1)*CHAR_HEIGHT);
                }
                if(isDisplayedChar(a))
                {
                    addCharToTextArea(e->textArea,a);
                    if(e->textArea->changes==true)
                        drawArea(e->textArea);
                    else
                        drawLines(e->textArea,e->textArea->topLeft.y+c->position.y*CHAR_HEIGHT,e->textArea->topLeft.y+(c->position.y+1)*CHAR_HEIGHT);
                    e->textArea->savedChanges = false;
                    e->menuArea->fileStateChanged = true;
                    e->menuArea->changes = true;
                }
                // logPieceTableNodes(e->textArea->pieceTable);
            }
        }
        drawEditor(e);
        delay(10);
    }
    return 0;
}
