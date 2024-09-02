#include "bsp.h"

static bool link_bsps(bsp_t *a, bsp_t *b)
{
    return list_add_ptr(&a->adjacents, b)
        && list_add_ptr(&b->adjacents, a);
}

static bool link_frontiers(list_t *a, list_t *b, int min_overlap)
{
    bsp_t *bsp_a = NULL;
    bsp_t *bsp_b = NULL;

    for (node_t *na = a->head; na; na = na->next) {
        bsp_a = na->data;
        for (node_t *nb = b->head; nb; nb = nb->next) {
            bsp_b = nb->data;
            if (rect_touching_overlap(bsp_a->rect, bsp_b->rect) < min_overlap)
                continue;
            if (!link_bsps(bsp_a, bsp_b))
                return false;
        }
    }
    return true;
}

bool bsp_match_adjacents(bsp_t *bsp)
{
    int min_overlap = 0;

    if (!bsp)
        return false;
    min_overlap = bsp->c_settings.room_link_min_touch;
    if (bsp_is_leaf(bsp))
        return true;
    if (bsp->split_orient == O_HORIZONTAL)
        return link_frontiers(&bsp->sub1->frontiers.south,
            &bsp->sub2->frontiers.north, min_overlap);
    return link_frontiers(&bsp->sub1->frontiers.east,
        &bsp->sub2->frontiers.west, min_overlap);
}
