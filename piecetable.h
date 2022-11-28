#include "color.h"

#ifndef NOTEIM_PIECETABLE_H_
#define NOTEIM_PIECETABLE_H_

#define MAX_LENGTH_BUFFER 2047

struct TextAttribute
{
    Color bg;
    Color fontColor;

    TextAttribute *prev;
    TextAttribute *next;
};

// TextAttributeList* initTextAttribute();
bool textAttributeIsEqual(TextAttribute *ta1, TextAttribute *ta2);

struct TextAttributesList
{
    unsigned int length;
    TextAttribute *first;
    TextAttribute *last;
};

// TextAtrributesList* initTextAttributesList();

struct Buffer
{
    TextAttributesList *textAttributesList;
    char text[MAX_LENGTH_BUFFER+1];
    // Maximum length will be 2047, last element is reserved for '\0'
    unsigned int length:10;
    Buffer *prev;
    Buffer *next;
};

Buffer* initBuffer();
bool bufferIsFull(Buffer *b);
bool addElementToBuffer(char e, TextAttribute *ta, Buffer *b);

struct BuffersList
{
    unsigned int length;
    Buffer *first;
    Buffer *last;
};

BuffersList* initBuffersList();
void addBuffer(BuffersList *bl, Buffer *b);
// void removeLastBuffer(BuffersList *bl);


struct PieceTableNode
{
    unsigned int bufferIndex;
    unsigned int start;
    unsigned int length;
    unsigned int numberNewLines;

    PieceTableNode *prev;
    PieceTableNode *next;
};

PieceTableNode* initPieceTableNode(unsigned int bufferIndex, unsigned int start, unsigned int length, unsigned int numberNewLines);
// PieceTableNode* modifyNode();

struct PieceTableNodesList
{
    unsigned int length;
    PieceTableNode *first;
    PieceTableNode *last;
};

PieceTableNodesList* initPieceTableNodesList();
// void addPieceTableNode(PieceTableNodesList *nl, PieceTableNode *n);
// void removeLastPieceTableNode(PieceTableNodeList *nl);


struct PieceTable
{
    BuffersList *buffersList;
    PieceTableNodesList *nodesList;
};

PieceTable* initPieceTable();

#endif // NOTEIM_PIECETABLE_H_
