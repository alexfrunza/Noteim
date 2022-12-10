#include <iostream>
#include "editor.h"
#include "piecetable.h"

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
    while(e->running)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            getmouseclick(WM_LBUTTONDOWN,x,y);
            Point newCursorPosition = {x/CHAR_WIDTH,y/CHAR_HEIGHT};
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
            if(a == 8)
            {
                // Backspace deletion.
            }
            if(ENTER_PRESSED)
            {
                drawCursorLine(e->textArea->cursor->position,true);
                addElementToPieceTable(e->textArea->pieceTable,e->textArea->cursor->position,'\n');
                e->textArea->pieceTable->numberOfLines++;
                e->textArea->changes = true;
            }
            if(TAB_PRESSED)
            {
                addElementToPieceTable(e->textArea->pieceTable,e->textArea->cursor->position,' ');
                addElementToPieceTable(e->textArea->pieceTable,e->textArea->cursor->position,' ');
                addElementToPieceTable(e->textArea->pieceTable,e->textArea->cursor->position,' ');
                addElementToPieceTable(e->textArea->pieceTable,e->textArea->cursor->position,' ');
                e->textArea->changes = true;
            }
            // Test scroll

            if(a == 'j')
            {
                if(e->textArea->firstLine > 0)
                {
                    e->textArea->firstLine--;
                    e->textArea->changes = true;
                }
            }
            else if(a=='k')
            {
                e->textArea->firstLine++;
                e->textArea->changes = true;
            }
            else if(a=='h')
            {
                if(e->textArea->firstColumn > 0)
                {
                    e->textArea->firstColumn--;
                    e->textArea->changes = true;
                }

            }
            else if(a=='l')
            {
                e->textArea->firstColumn++;
                e->textArea->changes = true;
            }
            else

                if(isDisplayedChar(a))
                {
                    addElementToPieceTable(e->textArea->pieceTable,e->textArea->cursor->position,a);
                    e->textArea->changes = true;
                }
        }
        drawEditor(e);
        delay(10);
    }
    return 0;
}
