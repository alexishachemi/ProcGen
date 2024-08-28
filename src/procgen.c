#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "procgen.h"

void __attribute__((constructor)) init_gen()
{
    srand(time(NULL));
}

bool procgen_init(procgen_t *pg)
{
    if (!pg)
        return false;
    list_init(&pg->corridor_segments);
    pg->initialized = true;
    return true;
}

void procgen_deinit(procgen_t *pg)
{
    if (!pg)
        return;
    bsp_deinit(&pg->bsp);
    automaton_deinit(&pg->automaton);
    list_clear_free(&pg->corridor_segments);
    pg->initialized = false;
}

bool procgen_generate(procgen_t *pg, vec2_t size)
{
    if (!pg || !bsp_init(&pg->bsp, (rect_t){{0, 0}, size})
        || !automaton_init(&pg->automaton, size))
        return false;
    pg->bsp.s_settings = pg->split_settings;
    pg->bsp.r_settings = pg->room_settings;
    pg->bsp.c_settings = pg->corridor_settings;
    pg->automaton.settings = pg->automaton_settings;
    return bsp_generate(&pg->bsp)
        && procgen_add_corridors(pg)
        && automaton_generate(&pg->automaton);
}
