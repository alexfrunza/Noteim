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
                // Maybe pop-up do you want to save the file, if the file isn't save.
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
        if(e->textArea->changes)
        {
            int current_y = 0;
            int current_x = 0;
            for(int i=0; i<lastBuffer->length; i++, current_x+=16)
            {
                if(lastBuffer->text[i] == '\n')
                {
                    current_y += 16;
                    current_x= -16;
                }
                char aux = lastBuffer->text[i+1];
                lastBuffer->text[i+1] = '\0';
                outtextxy(current_x, current_y, lastBuffer->text+i);
                lastBuffer->text[i+1] = aux;
            }
        }

        //drawEditor(e); // Trebuie mutat tot de mai sus in drawArea(TextArea *ta);
        delay(10);
    }
    return 0;
}
