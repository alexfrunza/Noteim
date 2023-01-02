#ifndef NOTEIM_HELPERS_H
#define NOTEIM_HELPERS_H

struct Point
{
    int x;
    int y;
};

bool isDisplayedChar(char x);
int numberOfChar(int x);
char* itoa(int x, int size_char);

#endif // NOTEIM_HELPERS_H
