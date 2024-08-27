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
    bsp_frontier_init(&bsp->frontiers);
    bsp->split_orient = O_NONE;
    list_init(&bsp->adjacents);
    bsp_tree_init(&bsp->tree);
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
    bsp->s_settings = parent->s_settings;
    bsp->r_settings = parent->r_settings;
    bsp->c_settings = parent->c_settings;
    return bsp;
}

void bsp_destroy(bsp_t *bsp)
{
    if (!bsp)
        return;
    bsp_destroy(bsp->sub1);
    bsp_destroy(bsp->sub2);
    bsp_frontier_deinit(&bsp->frontiers);
    list_clear(&bsp->adjacents, NULL);
    bsp_tree_deinit(&bsp->tree);
    free(bsp);
}

bool bsp_set_split_settings(bsp_t *bsp, int splits,
    float max_ratio, int same_split_percent)
{
    if (!bsp || splits < 0 || max_ratio < 2.0f
        || same_split_percent < 0 || same_split_percent > 100)
        return false;
    bsp->s_settings.max_ratio = max_ratio;
    bsp->s_settings.splits = splits;
    bsp->s_settings.same_split_percent = same_split_percent;
    return true;
}

bool bsp_set_room_settings(
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
    bsp->r_settings.max_ratio = max_ratio;
    bsp->r_settings.min_coverage_percent = min_coverage_percent;
    bsp->r_settings.max_coverage_percent = max_coverage_percent;
    bsp->r_settings.spacing_rate = spacing_rate;
    return true;
}

bool bsp_set_corridor_settings(
    bsp_t *bsp,
    int room_link_min_touch,
    float cycling_rate
)
{
    if (!bsp || cycling_rate < 0 || cycling_rate > 1)
        return false;
    bsp->c_settings.room_link_min_touch = room_link_min_touch;
    bsp->c_settings.cycling_rate = cycling_rate;
    return true;
}
