#include "bsp.h"
#include "utils.h"

void bsp_frontier_init(bsp_frontier_t *frontier)
{
    if (!frontier)
        return;
    list_init(&frontier->north);
    list_init(&frontier->south);
    list_init(&frontier->east);
    list_init(&frontier->west);
}

void bsp_frontier_deinit(bsp_frontier_t *frontier)
{
    if (!frontier)
        return;
    list_clear(&frontier->north, NULL);
    list_clear(&frontier->south, NULL);
    list_clear(&frontier->east, NULL);
    list_clear(&frontier->west, NULL);
}

static bool bsp_update_frontier_h(bsp_t *bsp)
{
    return list_add_list(&bsp->frontiers.north, &bsp->sub1->frontiers.north)
        && list_add_list(&bsp->frontiers.west, &bsp->sub1->frontiers.west)
        && list_add_list(&bsp->frontiers.west, &bsp->sub2->frontiers.west)
        && list_add_list(&bsp->frontiers.south, &bsp->sub2->frontiers.south)
        && list_add_list(&bsp->frontiers.east, &bsp->sub1->frontiers.east)
        && list_add_list(&bsp->frontiers.east, &bsp->sub2->frontiers.east);
}

static bool bsp_update_frontier_v(bsp_t *bsp)
{
    return list_add_list(&bsp->frontiers.north, &bsp->sub1->frontiers.north)
        && list_add_list(&bsp->frontiers.north, &bsp->sub2->frontiers.north)
        && list_add_list(&bsp->frontiers.west, &bsp->sub1->frontiers.west)
        && list_add_list(&bsp->frontiers.south, &bsp->sub1->frontiers.south)
        && list_add_list(&bsp->frontiers.south, &bsp->sub2->frontiers.south)
        && list_add_list(&bsp->frontiers.east, &bsp->sub2->frontiers.east);
}

bool bsp_generate_frontiers(bsp_t *bsp)
{
    if (!bsp)
        return false;
    if(bsp_is_leaf(bsp)) {
        return list_add_ptr(&bsp->frontiers.north, bsp)
            && list_add_ptr(&bsp->frontiers.west, bsp)
            && list_add_ptr(&bsp->frontiers.south, bsp)
            && list_add_ptr(&bsp->frontiers.east, bsp);
    }
    if (bsp->split_orient == O_HORIZONTAL)
        return bsp_update_frontier_h(bsp);
    return bsp_update_frontier_v(bsp);
}
