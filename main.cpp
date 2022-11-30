#include <iostream>
#include "helpers.h"
#include "editor.h"

using namespace std;

int main()
{
    Editor* e = initEditor();
    Buffer *lastBuffer = e->textArea->pieceTable->buffersList->last;
    char a;
    int x, y;
    while(e->running)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            getmouseclick(WM_LBUTTONDOWN,x,y);
            e->textArea->cursorPosition = {x/CHAR_WIDTH,y/CHAR_HEIGHT};
        }
        if(kbhit())
        {
            a = getch();
            if(a == 27) // Daca apesi ESC se inchide editorul
            {
                stopEditor(e);
                // Maybe pop-up do you want to save the file, if the file isn't saved.
                continue;
            }
            if(a == '\r')
            {
                addElementToBuffer('\n',lastBuffer);
                e->textArea->changes = true;
            }
            else if(isDisplayedChar(a))
            {
                addElementToBuffer(a,lastBuffer);
                e->textArea->changes = true;
            }
        }
        drawEditor(e);
        delay(10);
    }
    return 0;
}
