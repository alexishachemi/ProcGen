#include <math.h>
#include "rect.h"

static int min(int a, int b)
{
    if (a < b)
        return a;
    return b;
}

static int max(int a, int b)
{
    if (a > b)
        return a;
    return b;
}

vec2_t rect_center(rect_t r)
{
    return vec2_div_i(rect_end(r), 2);
}

rect_t rect_merge(rect_t r1, rect_t r2)
{
    vec2_t end1, end2;
    int x, y, endx, endy;

    end1 = rect_end(r1);
    end2 = rect_end(r2);
    x = min(r1.pos.x, r2.pos.x);
    y = min(r1.pos.y, r2.pos.y);
    endx = max(end1.x, end2.x);
    endy = max(end1.y, end2.y);
    return rect_new_e(vec2_new(x, y), vec2_new(endx, endy));
}

rect_t rect_grow(rect_t r, int n)
{
    return (rect_t){vec2_sub_i(r.pos, n), vec2_add_i(r.size, n)};
}
