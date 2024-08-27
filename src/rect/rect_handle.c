#include <stdio.h>
#include "utils.h"
#include "rect.h"

rect_t rect_new_i(int x, int y, int w, int h)
{
    return (rect_t){(vec2_t){x, y}, (vec2_t){w, h}};
}

void rect_print(rect_t r)
{
    printf("(p: (%d, %d), s: (%d, %d))", r.pos.x, r.pos.y, r.size.x, r.size.y);
}

int rect_touching_overlap(rect_t r1, rect_t r2)
{
    int x1 = r1.pos.x;
    int y1 = r1.pos.y;
    int w1 = r1.size.x;
    int h1 = r1.size.y;
    int x2 = r2.pos.x;
    int y2 = r2.pos.y;
    int w2 = r2.size.x;
    int h2 = r2.size.y;
    int overlap = 0;

    if (x1 + w1 == x2 || x2 + w2 == x1)
        overlap = min(y1 + h1, y2 + h2) - max(y1, y2);
    else if (y1 + h1 == y2 || y2 + h2 == y1)
        overlap = min(x1 + w1, x2 + w2) - max(x1, x2);
    return max(overlap, 0);
}
