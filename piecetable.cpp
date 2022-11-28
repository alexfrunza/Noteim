#include "piecetable.h"
#include "color.h"
#include <cstddef>

bool textAttributeIsEqual(TextAttribute *ta1, TextAttribute *ta2)
{
    if(!colorIsEqual(ta1->bg, ta2->bg)) return false;
    if(!colorIsEqual(ta1->fontColor, ta2->fontColor)) return false;
    return true;
}

bool bufferIsFull(Buffer *b)
{
    if (b->length >= MAX_LENGTH_BUFFER) return true;
    return false;
}

bool addElementToBuffer(char e, TextAttribute *ta, Buffer *b)
{
    if(bufferIsFull(b))
    {
        return false;
    }

    if(!textAttributeIsEqual(b->textAttributesList->last, ta))
    {
        // Add text attribute to list
    }

    b->text[b->length] = e;
    b->length++;
    return true;
}

Buffer* initBuffer()
{
    Buffer *b = new Buffer;
    b->textAttributesList = NULL; // TODO: implement textAttributes
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
    bl->length++;
    if(buffersListIsEmpty(bl))
    {
        b->next = NULL;
        b->prev = NULL;
        bl->first = b;
        bl->last = b;
        return;
    }

    bl->last->next = b;
    b->prev = bl->last;
    b->next = NULL;
    bl->last = b;
}

PieceTableNode* initPieceTableNode(unsigned int bufferIndex, unsigned int start, unsigned int length, unsigned int numberNewLines)
{
    PieceTableNode *n = new PieceTableNode;
    n->bufferIndex = bufferIndex;
    n->start = start;
    n->length = length;
    n->numberNewLines = numberNewLines;

    n->prev = NULL;
    n->next = NULL;
}

PieceTableNodesList* initPieceTableNodesList()
{
    PieceTableNodesList* ptnl = new PieceTableNodesList;
    ptnl->length = 0;
    ptnl->first = NULL;
    ptnl->last = NULL;
    return ptnl;
}

PieceTable* initPieceTable()
{
    PieceTable* pt = new PieceTable;
    pt->buffersList = initBuffersList();
    pt->nodesList = initPieceTableNodesList();
    return pt;
}
