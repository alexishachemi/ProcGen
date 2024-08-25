#include <stdlib.h>
#include "utils.h"

int rand_range(int from, int to)
{
    int max_range = to - from;
    if (max_range <= 0)
        return from;
    return from + (rand() % max_range);
}
