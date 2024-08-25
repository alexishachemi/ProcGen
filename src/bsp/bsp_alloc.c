#include <stdlib.h>
#include "bsp.h"

bsp_t *bsp_create(rect_t rect)
{
    bsp_t *bsp = NULL;

    bsp = malloc(sizeof(bsp_t));
    if (!bsp)
        return NULL;
    bsp->rect = rect;
    bsp->sub1 = NULL;
    bsp->sub2 = NULL;
    return bsp;
}

void bsp_destroy(bsp_t *bsp)
{
    if (!bsp)
        return;
    bsp_destroy(bsp->sub1);
    bsp_destroy(bsp->sub2);
    free(bsp);
}
