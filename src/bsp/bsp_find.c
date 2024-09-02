#include "bsp.h"

static void find(bsp_t *bsp, bsp_t **leaf)
{
    if (!bsp)
        return;
    if (!bsp_is_leaf(bsp)) {
        find(bsp->sub1, leaf);
        find(bsp->sub2, leaf);
    } else if (!*leaf || bsp->depth < (*leaf)->depth) {
        *leaf = bsp;
    }
}

bsp_t *bsp_find_shallow_leaf(bsp_t *bsp)
{
    bsp_t *leaf = NULL;

    if (!bsp)
        return NULL;
    find(bsp, &leaf);
    return leaf;
}
