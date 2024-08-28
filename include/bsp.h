#pragma once

#include <stdbool.h>
#include "rect.h"
#include "linked.h"

typedef struct bsp_s bsp_t;

enum orient_e {O_NONE = -1, O_VERTICAL = 0, O_HORIZONTAL = 1};

typedef struct {
    int splits;
    float max_ratio;
    int same_split_percent;
} bsp_split_settings_t;

typedef struct {
    float max_ratio;
    int min_coverage_percent;
    int max_coverage_percent;
    float spacing_rate;
} bsp_room_settings_t;

typedef struct {
    int room_link_min_touch;
    float cycling_rate;
} bsp_corridor_settings_t;

typedef struct {
    list_t north;
    list_t south;
    list_t east;
    list_t west;
} bsp_frontier_t;

typedef struct {
    bsp_t *bsp1;
    bsp_t *bsp2;
} bsp_link_t;

typedef struct {
    list_t visited;
    list_t links;
} bsp_nav_t;

typedef struct {
    list_t groups;
    list_t links;
    list_t unused_links;
} bsp_tree_t;

struct bsp_s {
    rect_t rect;
    rect_t room;
    bsp_t *sub1;
    bsp_t *sub2;
    orient_t split_orient;
    bsp_split_settings_t s_settings;
    bsp_room_settings_t r_settings;
    bsp_corridor_settings_t c_settings;
    bsp_frontier_t frontiers;
    list_t adjacents;
    list_t *group;
    bsp_tree_t tree;
};

bool bsp_init(bsp_t *bsp, rect_t rect);
bsp_t *bsp_create(rect_t rect);
bsp_t *bsp_from_parent(const bsp_t *bsp, rect_t rect);
void bsp_deinit(bsp_t *bsp);
void bsp_destroy(bsp_t *bsp);

bool bsp_generate(bsp_t *bsp);
bool bsp_split(bsp_t *bsp, orient_t orient);
bool bsp_add_room(bsp_t *bsp);
bool bsp_is_leaf(const bsp_t *bsp);
bool bsp_get_leaves(bsp_t *bsp, list_t *buf);

void bsp_frontier_init(bsp_frontier_t *frontier);
void bsp_frontier_deinit(bsp_frontier_t *frontier);
bool bsp_generate_frontiers(bsp_t *bsp);

bool bsp_nav_init(bsp_nav_t *nav);
void bsp_nav_deinit(bsp_nav_t *nav);
bool bsp_nav_traverse(bsp_nav_t *nav, bsp_t *bsp);

bool bsp_tree_init(bsp_tree_t *tree);
void bsp_tree_deinit(bsp_tree_t *tree);
bool bsp_generate_tree(bsp_tree_t *tree, bsp_t *bsp);
