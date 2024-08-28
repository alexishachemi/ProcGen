#pragma once

#include <stdbool.h>
#include <stdlib.h>
#include "vec2.h"

typedef enum {C_OFF = 0, C_ON = 1, C_ALWAYS_ON, C_ALWAYS_OFF} cell_t;

typedef struct {
    int iterations;
    int cell_on_minimum_neighbors;
    int noise_on_percent;
} automaton_settings_t;

typedef struct {
    vec2_t size;
    cell_t **map;
    automaton_settings_t settings;
} automaton_t;

bool automaton_init(automaton_t *a, vec2_t size);
void automaton_deinit(automaton_t *a);
bool automaton_set(automaton_t *a, int x, int y, cell_t state);
cell_t automaton_get(automaton_t *a, int x, int y);
bool automaton_add_noise(automaton_t *a);
bool automaton_generate(automaton_t *a);
