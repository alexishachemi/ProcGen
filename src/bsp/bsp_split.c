#include <stdlib.h>
#include <stdio.h>
#include "bsp.h"
#include "utils.h"

static vec2_t compute_h_bounds(rect_t rect, float max_ratio)
{
    int a, b = 0;

    a = rect.size.y / max_ratio;
    b = rect.size.y - a;
    return (vec2_t){a, b};
}

static vec2_t compute_v_bounds(rect_t rect, float max_ratio)
{
    int a, b = 0;

    a = rect.size.x / max_ratio;
    b = rect.size.x - a;
    return (vec2_t){a, b};
}

static bool split_horizontal(bsp_t *bsp, float max_ratio)
{
    rect_t sub1 = {0};
    rect_t sub2 = {0};
    vec2_t bounds = {0};
    int n = 0;

    bounds = compute_h_bounds(bsp->rect, max_ratio);
    n = rand_range(bounds.x, bounds.y);
    sub1 = (rect_t){
        bsp->rect.pos,
        {bsp->rect.size.x, n}
    };
    sub2 = (rect_t){
        {bsp->rect.pos.x, bsp->rect.pos.y + n},
        {bsp->rect.size.x, bsp->rect.size.y - sub1.size.y}
    };
    bsp->sub1 = bsp_create(sub1);
    if (!bsp->sub1)
        return false;
    bsp->sub2 = bsp_create(sub2);
    if (!bsp->sub2) {
        bsp_destroy(bsp->sub1);
        bsp->sub1 = NULL;
        return false;
    }
    return true;
}

static bool split_vertical(bsp_t *bsp, float max_ratio)
{
    rect_t sub1 = {0};
    rect_t sub2 = {0};
    vec2_t bounds = {0};
    int n = 0;

    bounds = compute_v_bounds(bsp->rect, max_ratio);
    n = rand_range(bounds.x, bounds.y);
    sub1 = (rect_t){
        bsp->rect.pos,
        {n, bsp->rect.size.y}
    };
    sub2 = (rect_t){
        {bsp->rect.pos.x + n, bsp->rect.pos.y},
        {bsp->rect.size.x - sub1.size.x, bsp->rect.size.y}
    };
    bsp->sub1 = bsp_create(sub1);
    if (!bsp->sub1)
        return false;
    bsp->sub2 = bsp_create(sub2);
    if (!bsp->sub2) {
        bsp_destroy(bsp->sub1);
        bsp->sub1 = NULL;
        return false;
    }
    return true;
}

static bool split(bsp_t *bsp, float max_ratio, int nb, int last_split, int ssp)
{
    bool split_success = false;
    int current_split = !last_split;

    if (!bsp)
        return false;
    if (rand() % 100 < ssp)
        current_split = last_split;
    if (nb <= 0)
        return true;
    if (current_split)
        split_success = split_horizontal(bsp, max_ratio);
    else
        split_success = split_vertical(bsp, max_ratio);
    if (!split_success)
        return false;
    return split(bsp->sub1, max_ratio, nb - 1, current_split, ssp)
        && split(bsp->sub2, max_ratio, nb - 1, current_split, ssp);
}

bool bsp_split(bsp_t *bsp, float max_ratio, int nb, int same_split_percentage)
{
    return split(bsp, max_ratio, nb, rand() % 2, same_split_percentage);
}
