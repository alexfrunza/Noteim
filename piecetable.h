#include "color.h"

#ifndef NOTEIM_PIECETABLE_H_
#define NOTEIM_PIECETABLE_H_

struct BufferElement
{
    char value;
    Color bg;
    Color font;
};

struct Buffer
{
    BufferElement value[1000];
    Buffer *prev;
    Buffer *next;
};

struct BuffersList
{
    unsigned int length;
    Buffer *head;
};

struct PieceTableNode
{
    unsigned int bufferIndex;
    unsigned int start;
    unsigned int length;
    unsigned int numberNewLines;
};

struct PieceTableNodesList
{
    unsigned int length;
    PieceTableNode *head;
};

struct PieceTable
{
    BuffersList *buffersList;
    PieceTableNodesList *nodesList;
};

#endif // NOTEIM_PIECETABLE_H_
