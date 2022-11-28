#ifndef NOTEIM_COLOR_H
#define NOTEIM_COLOR_H

struct Color
{
    unsigned int r:8;
    unsigned int g:8;
    unsigned int b:8;
};

int convertToBGIColor(Color c);

#endif // NOTEIM_COLOR_H
