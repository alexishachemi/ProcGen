#include <time.h>
#include <stdlib.h>
#include "bsp.h"

static bool generate(bsp_t *bsp, int splits, int split_dir)
{
    if (rand() % 100 < bsp->split_info.same_split_percent)
        split_dir = !split_dir;
    if (splits <= 0)
        return bsp_add_room(bsp);
    if (!bsp_split(bsp, split_dir))
        return false;
    return generate(bsp->sub1, splits - 1, !split_dir)
        && generate(bsp->sub2, splits - 1, !split_dir);
}

bool bsp_generate(bsp_t *bsp)
{
    if (!bsp)
        return false;
    return generate(bsp, bsp->split_info.splits, rand() % 2);
}

void __attribute__((constructor)) init_gen()
{
    srand(time(NULL));
}
