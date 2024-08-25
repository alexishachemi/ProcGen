#include <string.h>
#include <stdlib.h>
#include "bsp.h"

bsp_t *bsp_create(rect_t rect)
{
    bsp_t *bsp = NULL;

    bsp = malloc(sizeof(bsp_t));
    if (!bsp)
        return NULL;
    memset(bsp, 0, sizeof(bsp_t));
    bsp->rect = rect;
    return bsp;
}

bsp_t *bsp_from_parent(const bsp_t *parent, rect_t rect)
{
    bsp_t *bsp = NULL;

    if (!parent)
        return NULL;
    bsp = bsp_create(rect);
    if (!bsp)
        return NULL;
    bsp->split_info = parent->split_info;
    bsp->room_info = parent->room_info;
    return bsp;
}

void bsp_destroy(bsp_t *bsp)
{
    if (!bsp)
        return;
    bsp_destroy(bsp->sub1);
    bsp_destroy(bsp->sub2);
    free(bsp);
}

bool bsp_set_split_info(bsp_t *bsp, int splits,
    float max_ratio, int same_split_percent)
{
    if (!bsp || splits < 0 || max_ratio < 2.0f
        || same_split_percent < 0 || same_split_percent > 100)
        return false;
    bsp->split_info.max_ratio = max_ratio;
    bsp->split_info.splits = splits;
    bsp->split_info.same_split_percent = same_split_percent;
    return true;
}

bool bsp_set_room_info(
    bsp_t *bsp,
    float max_ratio,
    int min_coverage_percent,
    int max_coverage_percent,
    float spacing_rate
)
{
    if (!bsp || min_coverage_percent < 0 || max_coverage_percent > 100
        || min_coverage_percent > max_coverage_percent
        || spacing_rate < 0.0f || spacing_rate > 1.0f)
        return false;
    bsp->room_info.max_ratio = max_ratio;
    bsp->room_info.min_coverage_percent = min_coverage_percent;
    bsp->room_info.max_coverage_percent = max_coverage_percent;
    bsp->room_info.spacing_rate = spacing_rate;
    return true;
}
