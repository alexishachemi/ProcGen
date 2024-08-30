#include <stdlib.h>
#include <math.h>
#include "bsp.h"
#include "utils.h"

static vec2_t get_bounds(int smallest_size, int area, float max_ratio)
{
    int a, b = 0;

    b = min(sqrt(area), smallest_size);
    a = b / max_ratio;
    return (vec2_t){a, b};
}

static vec2_t generate_room_size(rect_t rect, const bsp_room_settings_t *info)
{
    int r_area = 0;
    int area = 0;
    vec2_t bounds = {0};
    vec2_t size = {0};

    r_area = rect_area(rect);
    area = rand_range(
        r_area * (info->min_coverage_percent / 100.0f),
        r_area * (info->max_coverage_percent / 100.0f)
    );
    bounds = get_bounds(min(rect.size.x, rect.size.y), area, info->max_ratio);
    if (rand() % 2) {
        size.x = rand_range(bounds.x, bounds.y);
        size.y = min(area / size.x, rect.size.y);
    } else {
        size.y = rand_range(bounds.x, bounds.y);
        size.x = min(area / size.y, rect.size.x);
    }
    return size;
}

static void place_room(bsp_t *bsp, vec2_t size)
{
    int available_spacing, spacing_offset = 0;
    vec2_t pos = {0};
    rect_t rect = bsp->rect;

    available_spacing = (rect.pos.x + (rect.size.x - size.x - 1)) - rect.pos.x;
    spacing_offset = available_spacing * bsp->r_settings.spacing_scale / 2;
    pos.x = rand_range(
        rect.pos.x + spacing_offset,
        rect.pos.x + available_spacing - spacing_offset
    );
    spacing_offset = 0;
    available_spacing = (rect.pos.y + (rect.size.y - size.y - 1)) - rect.pos.y;
    spacing_offset = available_spacing * bsp->r_settings.spacing_scale / 2;
    pos.y = rand_range(
        rect.pos.y + spacing_offset,
        rect.pos.y + available_spacing - spacing_offset
    );
    bsp->room = (rect_t){pos, size};
}

bool bsp_add_room(bsp_t *bsp)
{
    vec2_t size = {0};
    rect_t rect = {0};
    
    if (!bsp)
        return false;
    rect = bsp->rect;
    size = generate_room_size(rect, &bsp->r_settings);
    place_room(bsp, size);
    return true;
}

bool bsp_is_leaf(const bsp_t *bsp)
{
    return bsp && !bsp->sub1 && !bsp->sub2;
}

bool bsp_get_leaves(bsp_t *bsp, list_t *buf)
{
    if (!bsp || !buf)
        return false;
    if (bsp_is_leaf(bsp))
        return list_add_ptr(buf, bsp);
    return bsp_get_leaves(bsp->sub1, buf)
        && bsp_get_leaves(bsp->sub2, buf);
}
