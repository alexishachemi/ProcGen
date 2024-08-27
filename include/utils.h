#pragma once

#include "linked.h"

int min(int a, int b);
int max(int a, int b);
int clamp(int n, int min_val, int max_val);
int rand_range(int from, int to);
bool list_add_list(list_t *dest, list_t *src);
