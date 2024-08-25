#include <criterion/criterion.h>
#include "vec2.h"

Test(vec2, add)
{
    vec2_t a = {12, 5};
    vec2_t b = {48, 16};
    vec2_t c = vec2_add(a, b);

    cr_assert_eq(c.x, 60);
    cr_assert_eq(c.y, 21);
}

Test(vec2, add_int)
{
    vec2_t a = {75, 98};
    int b = 23;
    vec2_t c = vec2_add_i(a, b);

    cr_assert_eq(c.x, 98);
    cr_assert_eq(c.y, 121);
}

Test(vec2, sub)
{
    vec2_t a = {12, 5};
    vec2_t b = {48, 16};
    vec2_t c = vec2_sub(a, b);

    cr_assert_eq(c.x, -36);
    cr_assert_eq(c.y, -11);
}

Test(vec2, sub_int)
{
    vec2_t a = {75, 98};
    int b = 23;
    vec2_t c = vec2_sub_i(a, b);

    cr_assert_eq(c.x, 52);
    cr_assert_eq(c.y, 75);
}

Test(vec2, mul)
{
    vec2_t a = {12, 5};
    vec2_t b = {48, 16};
    vec2_t c = vec2_mul(a, b);

    cr_assert_eq(c.x, 576);
    cr_assert_eq(c.y, 80);
}

Test(vec2, mul_int)
{
    vec2_t a = {75, 98};
    int b = 23;
    vec2_t c = vec2_mul_i(a, b);

    cr_assert_eq(c.x, 1725);
    cr_assert_eq(c.y, 2254);
}

Test(vec2, div)
{
    vec2_t a = {12, 5};
    vec2_t b = {48, 16};
    vec2_t c = vec2_div(a, b);

    cr_assert_eq(c.x, 0);
    cr_assert_eq(c.y, 0);
    a = (vec2_t){100, 84};
    b = (vec2_t){4, 2};
    c = vec2_div(a, b);
    cr_assert_eq(c.x, 25);
    cr_assert_eq(c.y, 42);
    a = (vec2_t){100, 84};
    b = (vec2_t){4, 0};
    c = vec2_div(a, b);
    cr_assert_eq(c.x, 25);
    cr_assert_eq(c.y, 0);
}

Test(vec2, div_int)
{
    vec2_t a = {75, 98};
    int b = 23;
    vec2_t c = vec2_div_i(a, b);

    cr_assert_eq(c.x, 3);
    cr_assert_eq(c.y, 4);
    a = (vec2_t){100, 84};
    b = 4;
    c = vec2_div_i(a, b);
    cr_assert_eq(c.x, 25);
    cr_assert_eq(c.y, 21);
    a = (vec2_t){100, 84};
    b = 0;
    c = vec2_div_i(a, b);
    cr_assert_eq(c.x, 0);
    cr_assert_eq(c.y, 0);
}

Test(vec2, dist)
{
    vec2_t a = {0, 0};
    vec2_t b = {3, 4};
    float d = vec2_dist(a, b);

    cr_assert_float_eq(d, 5.0, 0.0001);
    a = (vec2_t){-3, -4};
    b = (vec2_t){0, 0};
    d = vec2_dist(a, b);
    cr_assert_float_eq(d, 5.0, 0.0001);
    a = (vec2_t){0, 0};
    b = (vec2_t){100, 50};
    d = vec2_dist(a, b);
    cr_assert_float_eq(d, 111.8034, 0.0001);
    a = (vec2_t){-100, -50};
    b = (vec2_t){100, 50};
    d = vec2_dist(a, b);
    cr_assert_float_eq(d, 223.6068, 0.0001);
}
