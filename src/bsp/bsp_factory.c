#include <string.h>
#include <stdlib.h>
#include "bsp.h"

bool bsp_init(bsp_t *bsp, rect_t rect)
{
    if (!bsp)
        return false;
    memset(bsp, 0, sizeof(bsp_t));
    bsp->rect = rect;
    bsp_frontier_init(&bsp->frontiers);
    bsp->split_orient = O_NONE;
    list_init(&bsp->adjacents);
    bsp_tree_init(&bsp->tree);
    return true;
}

bsp_t *bsp_create(rect_t rect)
{
    bsp_t *bsp = NULL;

    bsp = malloc(sizeof(bsp_t));
    if (!bsp_init(bsp, rect))
        return NULL;
    return bsp;
}

bsp_t *bsp_from_parent(const bsp_t *parent, rect_t rect)
{
    bsp_t *bsp = NULL;

    if (!parent)
        return NULL;
    bsp = bsp_create(rect);
    if (!bsp)
        return NULL;
    bsp->s_settings = parent->s_settings;
    bsp->r_settings = parent->r_settings;
    bsp->c_settings = parent->c_settings;
    bsp->depth = parent->depth + 1;
    return bsp;
}

void bsp_deinit(bsp_t *bsp)
{
    if (!bsp)
        return;
    bsp_destroy(bsp->sub1);
    bsp_destroy(bsp->sub2);
    bsp_frontier_deinit(&bsp->frontiers);
    list_clear(&bsp->adjacents, NULL);
    bsp_tree_deinit(&bsp->tree);    
}

void bsp_destroy(bsp_t *bsp)
{
    if (!bsp)
        return;
    bsp_deinit(bsp);
    free(bsp);
}
