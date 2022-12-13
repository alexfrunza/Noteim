#include <iostream>
#include "editor.h"
#include "piecetable.h"

#define ARROW_PRESSED a==0
#define ESC_PRESSED a==27
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
        cout<<"START: "<<ptn->start<<" LENGTH: "<<ptn->length<< " NUMBERNEWLINES: " << ptn->numberNewLines << " ADRESS: "<<ptn <<'\n';
        for(i=0; i<ptn->length; i++)
            cout << ptn->buffer->text[ptn->start+i];
        ptn = ptn->next;
    }

}

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
            // Must add Delete Deletion
            if(a == 8)
            {
                //drawCursorLine(c->position,true);
                removeCharFromTextArea(e->textArea);
                e->textArea->changes = true;
            }
            if(ENTER_PRESSED)
            {
                drawCursorLine(c->position,true);
                addCharToTextArea(e->textArea,'\n');
                e->textArea->changes = true;
            }
            if(TAB_PRESSED)
            {
                addCharToTextArea(e->textArea,' ');
                addCharToTextArea(e->textArea,' ');
                addCharToTextArea(e->textArea,' ');
                addCharToTextArea(e->textArea,' ');
                e->textArea->changes = true;
            }
            // Test scroll

            /*
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
            else*/
            if(isDisplayedChar(a))
            {
                addCharToTextArea(e->textArea,a);
                e->textArea->changes = true;
            }
           // e->textArea->changes = true;
            // Logging pentru nodurile din tabel
             logPieceTableNodes(e->textArea->pieceTable);

            /*
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
            */

        }
        drawEditor(e);
        delay(10);
    }
    return 0;
}
