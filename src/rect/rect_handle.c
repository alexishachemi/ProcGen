#include <stdio.h>
#include "rect.h"

rect_t rect_new(vec2_t pos, vec2_t size)
{
    return (rect_t){pos, size};
}

rect_t rect_new_i(int x, int y, int w, int h)
{
    return (rect_t){(vec2_t){x, y}, (vec2_t){w, h}};
}

void rect_print(rect_t r)
{
    printf("(p: (%d, %d), s: (%d, %d))", r.pos.x, r.pos.y, r.size.x, r.size.y);
}
