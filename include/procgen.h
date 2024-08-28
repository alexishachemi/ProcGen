#pragma once

#include "bsp.h"
#include "automaton.h"

typedef struct {
    vec2_t a;
    vec2_t b;
} segment_t;

typedef struct {
    bool initialized;
    bsp_t bsp;
    list_t corridor_segments;
    automaton_t automaton;
    bsp_split_settings_t split_settings;
    bsp_room_settings_t room_settings;
    bsp_corridor_settings_t corridor_settings;
    automaton_settings_t automaton_settings;
} procgen_t;

bool procgen_init(procgen_t *pg);
void procgen_deinit(procgen_t *pg);
bool procgen_generate(procgen_t *pg, vec2_t size);
bool procgen_add_corridors(procgen_t *pg);
