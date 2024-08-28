#include <stdlib.h>
#include "procgen.h"

static void *create_segment(void)
{
    segment_t *seg = NULL;

    seg = malloc(sizeof(segment_t));
    if (seg)
        *seg = (segment_t){(vec2_t){0, 0}, (vec2_t){0, 0}}; 
    return seg;
}

static segment_t *new_corridor_segment(procgen_t *pg)
{
    return list_add(&pg->corridor_segments, create_segment);
}

static bool add_l_shaped_corridor(procgen_t *pg, vec2_t from,
    vec2_t to, bool x_first)
{
    vec2_t a = {0};
    vec2_t b = {0};
    segment_t *seg1 = NULL;
    segment_t *seg2 = NULL;

    seg1 = new_corridor_segment(pg);
    seg2 = new_corridor_segment(pg);
    if (!seg1 || !seg2)
        return false;
    a = from;
    b = to;
    if (x_first) {
        seg1->a = a;
        seg1->b = (vec2_t){b.x, a.y};
        seg2->a = seg1->b;
        seg2->b = b;
        return true;
    }
    seg1->a = a;
    seg1->b = (vec2_t){a.x, b.y};
    seg2->a = seg1->b;
    seg2->b = b;
    return true;
}

static bool add_turning_corridor(procgen_t *pg, bsp_t *from, bsp_t *to)
{
    vec2_t c1, c2;
    orient_t orient;
    bool x_first;

    if (!rect_get_overlap_centers(from->rect, to->rect, &c1, &c2))
        return false;
    orient = rect_get_overlap_orientation(from->rect, to->rect);
    x_first = orient == O_HORIZONTAL;
    return add_l_shaped_corridor(pg, rect_center(from->room), c1, x_first)
        && add_l_shaped_corridor(pg, rect_center(to->room), c2, x_first);
}

static bool add_straight_corridor(procgen_t *pg, rect_t from, rect_t to)
{
    segment_t *seg = NULL;

    seg = new_corridor_segment(pg);
    if (!seg)
        return false;
    if (!rect_get_overlap_centers(from, to, &seg->a, &seg->b))
        return false;
    return true;
}

bool procgen_add_corridors(procgen_t *pg)
{
    bsp_link_t *l = NULL;

    if (!pg)
        return false;
    for (node_t *n = pg->bsp->tree.links.head; n; n = n->next) {
        l = n->data;
        if (add_straight_corridor(pg, l->bsp1->room, l->bsp2->room))
            continue;
        if (!add_turning_corridor(pg, l->bsp1, l->bsp2))
            return false;
    }
    return true;
}
