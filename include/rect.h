#pragma once

#include <stdbool.h>
#include "vec2.h"

typedef enum orient_e orient_t;

typedef struct {
    vec2_t pos;
    vec2_t size;
} rect_t;

rect_t rect_new_i(int x, int y, int w, int h);
void rect_print(rect_t r);

rect_t rect_new_e(vec2_t start, vec2_t end);
vec2_t rect_end(rect_t r);

vec2_t rect_center(rect_t r);
rect_t rect_merge(rect_t r1, rect_t r2);
rect_t rect_grow(rect_t r, int n);
int rect_area(rect_t r);
int rect_touching_overlap(rect_t a, rect_t b);
bool rect_get_overlap_centers(rect_t r1, rect_t r2, vec2_t *c1, vec2_t *c2);
orient_t rect_get_overlap_orientation(rect_t r1, rect_t r2);
