#include "utils.h"

int min(int a, int b)
{
    if (a < b)
        return a;
    return b;
}

int max(int a, int b)
{
    if (a > b)
        return a;
    return b;
}

int clamp(int n, int min_val, int max_val)
{
    return max(min(n, min_val), max_val);
}
