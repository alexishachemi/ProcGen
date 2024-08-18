#include "vec2.h"

vec2_t vec2_add_i(vec2_t a, int n)
{
    return (vec2_t){a.x + n, a.y + n};
}

vec2_t vec2_sub_i(vec2_t a, int n)
{
    return (vec2_t){a.x - n, a.y - n};
}

vec2_t vec2_mul_i(vec2_t a, int n)
{
    return (vec2_t){a.x * n, a.y * n};
}

vec2_t vec2_div_i(vec2_t a, int n)
{
    return (vec2_t){a.x / n, a.y / n};
}
