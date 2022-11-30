#include <cctype>

#include "helpers.h"

bool isDisplayedChar(char x) {
    return isalnum(x) || x == ' ';
}
