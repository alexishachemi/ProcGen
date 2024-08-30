#pragma once

#include <stdbool.h>
#include <stdlib.h>
#include "vec2.h"
#include "bsp.h"

#define CELL_NH_SIZE 8

typedef enum {C_OFF = 0, C_ON = 1, C_ALWAYS_ON, C_ALWAYS_OFF} cell_t;
typedef vec2_t cell_nh_t[CELL_NH_SIZE];
typedef enum {A_ISOLATED, A_CONNECTED} automaton_fill_state_t;

typedef struct {
    vec2_t a;
    vec2_t b;
} segment_t;

typedef struct {
    list_t cells;
    automaton_fill_state_t state;
} automaton_fill_t;

typedef struct {
    int iterations;
    int cell_on_minimum_neighbors;
    int noise_on_percent;
    int corridor_inner_size;
    int corridor_outer_size;
    int room_outline_size;
    bool apply_flood_fill;
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
bool automaton_pos_is_valid(automaton_t *a, int x, int y);
bool automaton_add_noise(automaton_t *a);
void automaton_get_cell_neihbors_pos(cell_nh_t nh, int x, int y);
int automaton_count_neighbors_on(automaton_t *a, int x, int y);
bool automaton_generate(automaton_t *a);
bool automaton_draw_rect(automaton_t *a, rect_t rect, cell_t cell);
bool automaton_draw_point(automaton_t *a, vec2_t pos, cell_t cell, int size);
bool automaton_draw_line(automaton_t *a, segment_t *s, cell_t cell, int size);
bool automaton_draw_corridors(automaton_t *a, list_t *segments);
bool automaton_draw_bsp_zones(automaton_t *a, list_t *zones);
bool automaton_c_constant(cell_t cell);
bool automaton_flood_fill(automaton_t *a);
bool automaton_off_cells_by_neighbors(automaton_t *a, int nh_count);
