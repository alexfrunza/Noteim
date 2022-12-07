#include <iostream>
#include "editor.h"

#define ARROW_PRESSED a==0
#define ESC_PRESSED a==27
#define ENTER_PRESSED a=='\r'
#define TAB_PRESSED a=='\t'

using namespace std;

int main()
{
    Editor* e = initEditor();
    char a;
    int x, y;
    Cursor *c = e->textArea->cursor;
    while(e->running)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            getmouseclick(WM_LBUTTONDOWN,x,y);
            Point newCursorPosition = {x/CHAR_WIDTH,y/CHAR_HEIGHT};
            if(x%CHAR_WIDTH>=CHAR_WIDTH/2)
                newCursorPosition.x++;
            moveCursor(e->textArea,newCursorPosition);
            continue;
        }
        if(kbhit())
        {
            a = getch();
            if(ARROW_PRESSED)
            {
                moveCursorByArrow(e->textArea,getch());
                continue;
            }
            if(ESC_PRESSED)
            {
                stopEditor(e);
                // Maybe pop-up do you want to save the file, if the file isn't saved.
                continue;
            }
            drawCursorLine(c->position,true);
            if(a == 8)
            {
                // Backspace deletion.
            }
            if(ENTER_PRESSED)
            {
                drawCursorLine(c->position,true);
                addElementToPieceTable(e->textArea->pieceTable,c->pieceTableNode,c->position,c->positionInNode,'\n');
                e->textArea->pieceTable->numberOfLines++;
            }
            if(TAB_PRESSED)
            {
                addElementToPieceTable(e->textArea->pieceTable,c->pieceTableNode,c->position,c->positionInNode,' ');
                addElementToPieceTable(e->textArea->pieceTable,c->pieceTableNode,c->position,c->positionInNode,' ');
                addElementToPieceTable(e->textArea->pieceTable,c->pieceTableNode,c->position,c->positionInNode,' ');
                addElementToPieceTable(e->textArea->pieceTable,c->pieceTableNode,c->position,c->positionInNode,' ');
            }
            if(isDisplayedChar(a))
                addElementToPieceTable(e->textArea->pieceTable,c->pieceTableNode,c->position,c->positionInNode,a);
            e->textArea->changes = true;

            int i;
            printf("\n");
        PieceTableNode *ptn = e->textArea->pieceTable->nodesList->first;
        while(ptn!=NULL)
        {
            i = 0;
            while(i<ptn->length)
            {
                printf("%c",ptn->buffer->text[i+ptn->start]);
                i++;
            }
            ptn = ptn->next;
        }


        }
        drawEditor(e);
        delay(10);
    }
    return 0;
}
