#pragma once

#include <stdbool.h>
#include "rect.h"
#include "linked.h"

typedef struct bsp_s bsp_t;

typedef enum {O_NONE = -1, O_VERTICAL = 0, O_HORIZONTAL = 1} orient_t;

typedef struct {
    float max_ratio;
    int splits;
    int same_split_percent;
} bsp_split_info_t;

typedef struct {
    float max_ratio;
    int min_coverage_percent;
    int max_coverage_percent;
    float spacing_rate;
    int link_min_touch_overlap;
} bsp_room_info_t;

typedef struct {
    list_t north;
    list_t south;
    list_t east;
    list_t west;
} bsp_frontier_t;

struct bsp_s {
    rect_t rect;
    rect_t room;
    bsp_t *sub1;
    bsp_t *sub2;
    orient_t split_orient;
    bsp_split_info_t split_info;
    bsp_room_info_t room_info;
    bsp_frontier_t frontiers;
    list_t adjacents;
};

bsp_t *bsp_create(rect_t rect);
bsp_t *bsp_from_parent(const bsp_t *bsp, rect_t rect);
void bsp_destroy(bsp_t *bsp);
bool bsp_set_split_info(
    bsp_t *bsp,
    int splits,
    float max_ratio,
    int same_split_percent
);
bool bsp_set_room_info(
    bsp_t *bsp,
    float max_ratio,
    int min_coverage_percent,
    int max_coverage_percent,
    float spacing_rate,
    int link_min_touch_overlap
);
bool bsp_generate(bsp_t *bsp);
bool bsp_split(bsp_t *bsp, orient_t orient);
bool bsp_add_room(bsp_t *bsp);
bool bsp_is_leaf(const bsp_t *bsp);

void bsp_frontier_init(bsp_frontier_t *frontier);
void bsp_frontier_deinit(bsp_frontier_t *frontier);
bool bsp_generate_frontiers(bsp_t *bsp);
