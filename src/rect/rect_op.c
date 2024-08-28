#include <math.h>
#include "rect.h"
#include "utils.h"

vec2_t rect_center(rect_t r)
{
    return (vec2_t){r.pos.x + r.size.x / 2, r.pos.y + r.size.y / 2};
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
    return rect_new_e(
        (vec2_t){x, y},
        (vec2_t){endx, endy}
    );
}

rect_t rect_grow(rect_t r, int n)
{
    return (rect_t){vec2_sub_i(r.pos, n), vec2_add_i(r.size, n * 2)};
}

int rect_area(rect_t r)
{
    return r.size.x * r.size.y;
}
