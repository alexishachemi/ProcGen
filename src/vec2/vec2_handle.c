#include <stdio.h>
#include <math.h>
#include "vec2.h"
#include "utils.h"

float vec2_dist(vec2_t a, vec2_t b)
{
    return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
}

static int int_move_towards(int from, int to, int delta)
{
    if (from < to)
        return min(from + delta, to);
    if (from > to)
        return max(from - delta, to);
    return from;
}

vec2_t vec2_move_towards(vec2_t from, vec2_t to, int delta)
{
    return (vec2_t){
        int_move_towards(from.x, to.x, delta),
        int_move_towards(from.y, to.y, delta)
    };
}

void vec2_print(vec2_t vec)
{
    printf("(%d, %d)", vec.x, vec.y);
}
