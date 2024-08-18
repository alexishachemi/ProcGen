#pragma once

#include "vec2.h"

typedef struct {
    vec2_t pos;
    vec2_t size;
} rect_t;

rect_t rect_new(vec2_t pos, vec2_t size);
rect_t rect_new_i(int x, int y, int w, int h);
void rect_print(rect_t r);

rect_t rect_new_e(vec2_t start, vec2_t end);
vec2_t rect_end(rect_t r);

vec2_t rect_center(rect_t r);
rect_t rect_merge(rect_t r1, rect_t r2);
rect_t rect_grow(rect_t r, int n);
