#include <stdio.h>
#include <math.h>
#include "vec2.h"

float vec2_dist(vec2_t a, vec2_t b)
{
    return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
}

void vec2_print(vec2_t vec)
{
    printf("(%d, %d)", vec.x, vec.y);
}
