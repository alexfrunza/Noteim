#include "piecetable.h"

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

void getWhereLineStarts(PieceTable* pt, long line, PieceTableNode* &ptn, long &indexOfLine)
{
    if(pt->numberOfLines < line)
    {
        ptn = NULL;
        return;
    }

    ptn = pt->nodesList->first;
    if(ptn == NULL)
    {
        return;
    }
    long currentLine = 0;
    long linesCounter = ptn->numberNewLines;
    long indexLimitOfNode = ptn->start + ptn->length;

    if(linesCounter < line)
    {
        long prevLinesCounter;

        do
        {
            ptn  = ptn->next;
            indexLimitOfNode = ptn->start + ptn->length;
            prevLinesCounter = linesCounter;
            linesCounter += ptn->numberNewLines;
        }
        while(linesCounter < line);

        currentLine = prevLinesCounter;
    }

    indexOfLine = ptn->start - 1;
    while(currentLine < line && indexOfLine < indexLimitOfNode)
    {
        indexOfLine++;
        if(ptn->buffer->text[indexOfLine] == '\n') currentLine++;
    }

    indexOfLine++;
    if(indexOfLine >= indexLimitOfNode)
    {
        if(ptn->next == NULL)
        {
            ptn = NULL;
            return;
        }
        else if(ptn->next != NULL)
        {
            ptn = ptn->next;
            indexOfLine = ptn->start;
        }
    }
}

void emptyPieceTable(PieceTable *pt)
{
    emptyBuffersList(pt->buffersList);
    emptyPieceTableNodesList(pt->nodesList);
}
