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
                moveCursorByArrow(e->textArea,getch());
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
                addElementToPieceTable(e->textArea->pieceTable,e->textArea->cursorPosition,'\n');
            if(TAB_PRESSED)
            {
                addElementToPieceTable(e->textArea->pieceTable,e->textArea->cursorPosition,' ');
                addElementToPieceTable(e->textArea->pieceTable,e->textArea->cursorPosition,' ');
                addElementToPieceTable(e->textArea->pieceTable,e->textArea->cursorPosition,' ');
                addElementToPieceTable(e->textArea->pieceTable,e->textArea->cursorPosition,' ');
            }
            if(isDisplayedChar(a))
                addElementToPieceTable(e->textArea->pieceTable,e->textArea->cursorPosition,a);
            e->textArea->changes = true;
        }
        drawEditor(e);
        delay(10);
    }
    return 0;
}
