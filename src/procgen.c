#include "procgen.h"

bool procgen_init(procgen_t *pg)
{
    if (!pg)
        return false;
    pg->bsp = NULL;
    list_init(&pg->corridor_segments);
    return true;
}

void procgen_deinit(procgen_t *pg)
{
    if (!pg)
        return;
    bsp_destroy(pg->bsp);
    list_clear_free(&pg->corridor_segments);
}

bool procgen_generate(procgen_t *pg)
{
    return bsp_generate(pg->bsp)
        && procgen_add_corridors(pg);
}

bool procgen_add_corridors(procgen_t *pg)
{
    return true;
}
