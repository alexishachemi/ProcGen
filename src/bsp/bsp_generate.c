#include <stdlib.h>
#include "bsp.h"
#include "utils.h"

static bool generate_data(bsp_t *bsp)
{
    if (!bsp)
        return false;
    if (bsp_is_leaf(bsp) && !bsp_add_room(bsp))
        return false;
    if (bsp->sub1 && !generate_data(bsp->sub1))
        return false;
    if (bsp->sub2 && !generate_data(bsp->sub2))
        return false;
    return bsp_generate_frontiers(bsp)
        && bsp_match_adjacents(bsp);   
}

bool bsp_generate(bsp_t *bsp)
{
    if (!bsp)
        return false;
    return bsp_split(bsp)
        && generate_data(bsp)
        && bsp_generate_tree(&bsp->tree, bsp);
}
