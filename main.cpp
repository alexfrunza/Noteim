#include <iostream>
#include "window.cpp"

using namespace std;

int main()
{
    Window* nW = initializeWindow();
    BuffersList* bl = nW->text->pieceTable->buffersList;
    char a;
    int i;
    while(1)
        if(kbhit())
        {
            a = getch();
            if(bl->length==0 || bufferIsFull(bl->last))
                addBuffer(bl,initBuffer());
            cout << bl->length << ' '; // Debugging
            addElementToBuffer(a,bl->last);
            cout << bl->last->length << ' '; // Debugging
            for(i=0; i<bl->last->length; i++) // Nu asta e afisarea, aici doar vreau sa vad ca adaug in buffer
                cout << bl->last->text[i];
        }
    return 0;
}
