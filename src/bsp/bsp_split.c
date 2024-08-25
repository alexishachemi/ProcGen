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

static bool split_horizontal(bsp_t *bsp)
{
    rect_t sub1 = {0};
    rect_t sub2 = {0};
    vec2_t bounds = {0};
    int n = 0;

    bounds = compute_h_bounds(bsp->rect, bsp->split_info.max_ratio);
    n = rand_range(bounds.x, bounds.y);
    sub1 = (rect_t){
        bsp->rect.pos,
        {bsp->rect.size.x, n}
    };
    sub2 = (rect_t){
        {bsp->rect.pos.x, bsp->rect.pos.y + n},
        {bsp->rect.size.x, bsp->rect.size.y - sub1.size.y}
    };
    bsp->sub1 = bsp_from_parent(bsp, sub1);
    if (!bsp->sub1)
        return false;
    bsp->sub2 = bsp_from_parent(bsp, sub2);
    if (!bsp->sub2) {
        bsp_destroy(bsp->sub1);
        bsp->sub1 = NULL;
        return false;
    }
    return true;
}

static bool split_vertical(bsp_t *bsp)
{
    rect_t sub1 = {0};
    rect_t sub2 = {0};
    vec2_t bounds = {0};
    int n = 0;

    bounds = compute_v_bounds(bsp->rect, bsp->split_info.max_ratio);
    n = rand_range(bounds.x, bounds.y);
    sub1 = (rect_t){
        bsp->rect.pos,
        {n, bsp->rect.size.y}
    };
    sub2 = (rect_t){
        {bsp->rect.pos.x + n, bsp->rect.pos.y},
        {bsp->rect.size.x - sub1.size.x, bsp->rect.size.y}
    };
    bsp->sub1 = bsp_from_parent(bsp, sub1);
    if (!bsp->sub1)
        return false;
    bsp->sub2 = bsp_from_parent(bsp, sub2);
    if (!bsp->sub2) {
        bsp_destroy(bsp->sub1);
        bsp->sub1 = NULL;
        return false;
    }
    return true;
}

bool bsp_split(bsp_t *bsp, int split_dir)
{
    bool split_success = false;

    if (!bsp)
        return false;
    if (split_dir)
        split_success = split_horizontal(bsp);
    else
        split_success = split_vertical(bsp);
    return split_success;
}
