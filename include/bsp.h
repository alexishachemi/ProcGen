#pragma once

#include <stdbool.h>
#include "rect.h"

typedef struct bsp_s bsp_t;

struct bsp_s {
    rect_t rect;
    bsp_t *sub1;
    bsp_t *sub2;
};

bsp_t *bsp_create(rect_t rect);
void bsp_destroy(bsp_t *bsp);

bool bsp_split(bsp_t *bsp, float max_ratio, int nb, int same_split_percentage);
bool bsp_is_leaf(const bsp_t *bsp);
