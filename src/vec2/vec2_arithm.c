#include "vec2.h"

vec2_t vec2_add(vec2_t a, vec2_t b)
{
    return (vec2_t){a.x + b.x, a.y + b.y};
}

vec2_t vec2_sub(vec2_t a, vec2_t b)
{
    return (vec2_t){a.x - b.x, a.y - b.y};
}

vec2_t vec2_mul(vec2_t a, vec2_t b)
{
    return (vec2_t){a.x * b.x, a.y * b.y};
}

vec2_t vec2_div(vec2_t a, vec2_t b)
{
    vec2_t c = {0, 0};

    if (b.x != 0)
        c.x = a.x / b.x;
    if (b.y != 0)
        c.y = a.y / b.y;
    return c;
}
