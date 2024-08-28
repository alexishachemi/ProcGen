#pragma once

typedef struct {
    int x;
    int y;
} vec2_t;

float vec2_dist(vec2_t a, vec2_t b);
vec2_t vec2_move_towards(vec2_t from, vec2_t to, int delta);
void vec2_print(vec2_t vec);

vec2_t vec2_add(vec2_t a, vec2_t b);
vec2_t vec2_sub(vec2_t a, vec2_t b);
vec2_t vec2_mul(vec2_t a, vec2_t b);
vec2_t vec2_div(vec2_t a, vec2_t b);

vec2_t vec2_add_i(vec2_t a, int n);
vec2_t vec2_sub_i(vec2_t a, int n);
vec2_t vec2_mul_i(vec2_t a, int n);
vec2_t vec2_div_i(vec2_t a, int n);
