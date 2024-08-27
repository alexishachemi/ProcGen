#include <stdlib.h>
#include "bsp.h"

bool bsp_nav_init(bsp_nav_t *nav)
{
    if (!nav)
        return false;
    list_init(&nav->links);
    list_init(&nav->visited);
    return true;
}

void bsp_nav_deinit(bsp_nav_t *nav)
{
    if (!nav)
        return;
    list_clear_free(&nav->links);
    list_clear(&nav->visited, NULL);
}

static bsp_link_t *bsp_link(bsp_t *bsp1, bsp_t *bsp2)
{
    bsp_link_t *link = NULL;

    if (!bsp1 || !bsp2)
        return NULL;
    link = malloc(sizeof(bsp_link_t));
    if (!link)
        return NULL;
    link->bsp1 = bsp1;
    link->bsp2 = bsp2;
    return link;
}

static bool visit(bsp_nav_t *nav, bsp_t *bsp)
{
    return list_add_ptr(&nav->visited, bsp);
}

static bool add_link(bsp_nav_t *nav, bsp_t *bsp1, bsp_t *bsp2)
{
    bsp_link_t *link = NULL;

    link = bsp_link(bsp1, bsp2);
    if (!link)
        return false;
    if (!list_add_ptr(&nav->links, link)) {
        free(link);
        return false;
    }
    return true;
}

static bool is_visited(bsp_nav_t *nav, bsp_t *bsp)
{
    return nav && bsp && list_has_ptr(&nav->visited, bsp);
}

bool bsp_nav_traverse(bsp_nav_t *nav, bsp_t *bsp)
{
    if (!nav || !bsp)
        return false;
    if (!bsp_is_leaf(bsp))
        return bsp_nav_traverse(nav, bsp->sub1);
    if (!visit(nav, bsp))
        return false;
    for (node_t *n = bsp->adjacents.head; n; n = n->next) {
        if (!add_link(nav, bsp, n->data))
            return false;
        if (is_visited(nav, n->data))
            continue;
        if (!bsp_nav_traverse(nav, n->data))
            return false;
    }
    return true;
}
