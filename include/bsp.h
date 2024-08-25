#pragma once

#include <stdbool.h>
#include "rect.h"

typedef struct bsp_s bsp_t;

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
} bsp_room_info_t;

struct bsp_s {
    rect_t rect;
    rect_t room;
    bsp_t *sub1;
    bsp_t *sub2;
    bsp_split_info_t split_info;
    bsp_room_info_t room_info;
};

bsp_t *bsp_create(rect_t rect);
bsp_t *bsp_from_parent(const bsp_t *bsp, rect_t rect);
void bsp_destroy(bsp_t *bsp);
bool bsp_set_split_info(bsp_t *bsp, int splits, float max_ratio, int same_split_percent);
bool bsp_set_room_info(bsp_t *bsp, float max_ratio,
    int min_coverage_percent, int max_coverage_percent, float spacing_rate);
bool bsp_generate(bsp_t *bsp);
bool bsp_split(bsp_t *bsp, int split_dir);
bool bsp_add_room(bsp_t *bsp);
bool bsp_is_leaf(const bsp_t *bsp);