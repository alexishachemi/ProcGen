#pragma once

#include "bsp.h"

typedef struct {
    vec2_t a;
    vec2_t b;
} segment_t;

typedef struct {
    bsp_t *bsp;
    list_t corridor_segments;
} procgen_t;

bool procgen_init(procgen_t *pg);
void procgen_deinit(procgen_t *pg);
bool procgen_generate(procgen_t *pg);
bool procgen_add_corridors(procgen_t *pg);
