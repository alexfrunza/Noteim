#include "color.h"
#include <graphics.h>

int convertToBGIColor(Color c) {
    return COLOR(c.r, c.g, c.b);
}
