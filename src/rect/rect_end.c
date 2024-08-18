#include "rect.h"

rect_t rect_new_e(vec2_t start, vec2_t end)
{
    return (rect_t){start, vec2_sub(end, start)};
}

vec2_t rect_end(rect_t r)
{
    return vec2_add(r.pos, r.size);
}
