#include <iostream>
#include "helpers.h"
#include "editor.h"

using namespace std;

int main()
{
    Editor* e = initEditor();
    Buffer *lastBuffer = e->textArea->pieceTable->buffersList->last;
    while(e->running)
    {
        if(kbhit())
        {
            char a;
            a = getch();
            if(a == 27) // Daca apesi ESC se inchide editorul
            {
                stopEditor(e);
                // Maybe pop-up do you want to save the file, if the file isn't saved.
                continue;
            }
            else if(a == '\r')
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
