#include <stdlib.h>
#include "helpers.h"

bool isDisplayedChar(char x)
{
    return x>=32 && x<=126;
}

bool isNumber(char x) {
    return '0' <= x && x <= '9';
}

int numberOfChar(int x) {
    if(x == 0) return 1;
    int res = 0;

    while(x) {
        x/=10;
        res++;
    }
    return res;
}

// please free memory after using the value returned by this function
char* itoa(int x, int size_char) {
    char *res = (char*) malloc(sizeof(char) * size_char + 1);
    res[size_char] = '\0';

    int nC = numberOfChar(x);
    for(int i=size_char-1, j=0; i>=0 && j < nC; i--, j++) {
        res[i] = x%10 + '0';
        x/=10;
    }

    for(int i=size_char - nC - 1;i>=0;i--) {
            res[i] = ' ';
    }

    return res;
}
