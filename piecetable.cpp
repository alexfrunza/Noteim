#include "piecetable.h"
#include <cstdio>

#include <iostream>
using namespace std;

bool bufferIsFull(Buffer *b)
{
    if (b->length >= MAX_LENGTH_BUFFER) return true;
    return false;
}

bool addElementToBuffer(char e, Buffer *b)
{
    if(bufferIsFull(b))
        return false;

    b->text[b->length] = e;
    b->length++;
    return true;
}

Buffer* initBuffer()
{
    Buffer *b = new Buffer;
    b->length = 0;
    b->prev = NULL;
    b->next = NULL;
    return b;
}

BuffersList* initBuffersList()
{
    BuffersList* bl = new BuffersList;
    bl->length = 0;
    bl->first = NULL;
    bl->last = NULL;
    return bl;
}

bool buffersListIsEmpty(BuffersList *bl)
{
    if(bl->length == 0) return true;
    return false;
}

void addBuffer(BuffersList *bl, Buffer *b)
{
    if(buffersListIsEmpty(bl))
    {
        b->next = NULL;
        b->prev = NULL;
        bl->first = b;
        bl->last = b;
        bl->length++;
        return;
    }

    bl->last->next = b;
    b->prev = bl->last;
    b->next = NULL;
    bl->last = b;
    bl->length++;
}

void removeLastBuffer(BuffersList *bl)
{
    if(bl->length==0)
        return;
    if(bl->length==1)
    {
        delete bl->first;
        bl->first = bl->last = NULL;
        bl->length--;
        return;
    }
    bl->last = bl->last->prev;
    delete bl->last->next;
    bl->last->next = NULL;
    bl->length--;
}

void emptyBuffersList(BuffersList *bl)
{
    while(bl->length > 0)
    {
        removeLastBuffer(bl);
    }
}

PieceTableNode* initPieceTableNode(Buffer* buffer, unsigned int start, unsigned int length, unsigned int numberNewLines)
{
    PieceTableNode *n = new PieceTableNode;
    n->buffer = buffer;
    n->start = start;
    n->length = length;
    n->numberNewLines = numberNewLines;

    n->prev = NULL;
    n->next = NULL;
    return n;
}

PieceTableNodesList* initPieceTableNodesList()
{
    PieceTableNodesList* ptnl = new PieceTableNodesList;
    ptnl->length = 0;
    ptnl->first = NULL;
    ptnl->last = NULL;
    return ptnl;
}

void addPieceTableNode(PieceTableNodesList *nl, PieceTableNode *n)
{
    if(nl->length==0)
        nl->first = nl->last = n;
    else
    {
        n->prev = nl->last;
        nl->last->next = n;
        nl->last = n;
    }
    nl->length++;
}

void removeLastPieceTableNode(PieceTableNodesList *nl)
{
    if(nl->length==0)
        return;
    if(nl->length==1)
    {
        delete nl->first;
        nl->first = nl->last = NULL;
        nl->length--;
        return;
    }
    nl->last = nl->last->prev;
    delete nl->last->next;
    nl->last->next = NULL;
    nl->length--;
}

void emptyPieceTableNodesList(PieceTableNodesList *nl)
{
    while(nl->length > 0)
    {
        removeLastPieceTableNode(nl);
    }
}

PieceTable* initPieceTable()
{
    PieceTable* pt = new PieceTable;
    pt->buffersList = initBuffersList();
    pt->nodesList = initPieceTableNodesList();
    pt->numberOfLines = 0;
    return pt;
}

void addElementToPieceTable(PieceTable *pt, PieceTableNode* &destNode, Point &position, unsigned int &positionInNode, char newLetter)
{
    if(bufferIsFull(pt->buffersList->last))
        addBuffer(pt->buffersList,initBuffer()); // Ce fac cu cursorul?
    addElementToBuffer(newLetter, pt->buffersList->last);


    if(positionInNode==0 && destNode->prev!=NULL)
    {
        destNode = destNode->prev;
        positionInNode = destNode->length;
    }

    if(destNode->buffer==pt->buffersList->last && positionInNode==destNode->length && destNode->start+destNode->length==pt->buffersList->last->length-1)
    {
        // Add at the end of node
        destNode->length++;
        positionInNode++;
        if(newLetter=='\n')
        {
            position = {0,position.y+1};
            destNode->numberNewLines++;
            pt->numberOfLines++;
        }
        else
            position.x++;
        return;
    }

    PieceTableNode *newNode = initPieceTableNode(pt->buffersList->last,pt->buffersList->last->length-1,1,newLetter=='\n'?1:0);

    if(positionInNode==destNode->length)
    {
        // Add Node after
        if(destNode->next!=NULL)
        {
            newNode->next = destNode->next;
            destNode->next->prev = newNode;
        }
        else
            pt->nodesList->last = newNode;
        newNode->prev = destNode;
        destNode->next = newNode;
        pt->nodesList->length++;

        if(newLetter=='\n')
        {
            position = {0,position.y+1};
            pt->numberOfLines++;
        }
        else
            position.x++;
        destNode = newNode;
        positionInNode = 1;
        return;
    }

    if(positionInNode==0)
    {
        if(destNode->prev!=NULL)
        {
            newNode->prev = destNode->prev;
            destNode->prev->next = newNode;
        }
        else
            pt->nodesList->first = newNode;
        newNode->next = destNode;
        destNode->prev = newNode;
        pt->nodesList->length++;

        if(newLetter=='\n')
        {
            position = {0,position.y+1};
            pt->numberOfLines++;
        }
        else
            position.x++;
        destNode = newNode;
        positionInNode = 1;
        return;
    }

    {
        PieceTableNode *rightSide = initPieceTableNode(destNode->buffer,destNode->start+positionInNode,destNode->length-positionInNode-1,0);
        for(int i=rightSide->start+rightSide->length-1; i>=(int)rightSide->start; i--)
            if(rightSide->buffer->text[i]=='\n')
                rightSide->numberNewLines++;

        destNode->numberNewLines -= rightSide->numberNewLines;
        destNode->length = positionInNode+1;


        if(destNode->next!=NULL)
        {
            destNode->next->prev = rightSide;
            rightSide->next = destNode->next;
        }
        else
            pt->nodesList->last = rightSide;
        rightSide->prev = newNode;
        newNode->next = rightSide;
        destNode->next = newNode;
        newNode->prev = destNode;

        if(newLetter=='\n')
        {
            position = {0,position.y++};
            pt->numberOfLines++;
        }
        else
            position.x++;
        destNode = newNode;
        positionInNode = 1;
        pt->nodesList->length+=2;

        return;
    }
}

void getFirstNodeWhereAbsoluteLineIs(PieceTable* pt, unsigned int line, PieceTableNode* &startPtn, unsigned int &linesUntil)
{
    startPtn = pt->nodesList->first;
    unsigned int linesCounter = startPtn->numberNewLines;

    if(((long)line - 1) < (long)linesCounter)
    {
        linesUntil = 0;
        return;
    }

    unsigned int prevLinesCounter;

    do
    {
        startPtn  = startPtn->next;
        prevLinesCounter = linesCounter;
        linesCounter += startPtn->numberNewLines;
    }
    while((long)linesCounter <= (long)(line - 1));

    linesUntil = prevLinesCounter;
}

void emptyPieceTable(PieceTable *pt)
{
    emptyBuffersList(pt->buffersList);
    emptyPieceTableNodesList(pt->nodesList);
}
