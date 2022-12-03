#include "color.h"
#include "helpers.h"

#ifndef NOTEIM_PIECETABLE_H
#define NOTEIM_PIECETABLE_H

#define MAX_LENGTH_BUFFER 511


struct Buffer
{
    char text[MAX_LENGTH_BUFFER+1];
    // Maximum length will be 511, last element is reserved for '\0'
    unsigned int length:10;
    Buffer *prev;
    Buffer *next;
};

Buffer* initBuffer();
bool bufferIsFull(Buffer *b);
bool addElementToBuffer(char e, Buffer *b);

struct BuffersList
{
    unsigned int length;
    Buffer *first;
    Buffer *last;
};

BuffersList* initBuffersList();
void addBuffer(BuffersList *bl, Buffer *b);
void removeLastBuffer(BuffersList *bl);


struct PieceTableNode
{
    Buffer *buffer;
    unsigned int start;
    unsigned int length;
    unsigned int numberNewLines;

    PieceTableNode *prev;
    PieceTableNode *next;
};

PieceTableNode* initPieceTableNode(Buffer* buffer, unsigned int start, unsigned int length, unsigned int numberNewLines);
// PieceTableNode* modifyNode();

struct PieceTableNodesList
{
    unsigned int length;
    PieceTableNode *first;
    PieceTableNode *last;
};

PieceTableNodesList* initPieceTableNodesList();
void addPieceTableNode(PieceTableNodesList *nl, PieceTableNode *n);
void removeLastPieceTableNode(PieceTableNodesList *nl);

struct PieceTable
{
    BuffersList *buffersList;
    PieceTableNodesList *nodesList;
    unsigned int numberOfLines;
};

PieceTable* initPieceTable();
void addElementToPieceTable(PieceTable* pt, Point &position, char newLetter);
void getFirstNodeWhereAbsoluteLineIs(PieceTable* pt, unsigned int line, PieceTableNode* &startPtn, unsigned int &linesUntil);

#endif // NOTEIM_PIECETABLE_H
