#include <graphics.h>

#include "color.h"

int convertToBGIColor(Color c) {
    return COLOR(c.r, c.g, c.b);
}

bool colorIsEqual(Color c1, Color c2) {
    if(c1.r != c2.r) return false;
    if(c1.g != c2.g) return false;
    if(c1.b != c2.b) return false;
    return true;
}
