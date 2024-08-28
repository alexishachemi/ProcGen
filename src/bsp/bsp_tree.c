#include <stdlib.h>
#include "bsp.h"
#include "utils.h"

bool bsp_tree_init(bsp_tree_t *tree)
{
    if (!tree)
        return false;
    list_init(&tree->groups);
    list_init(&tree->links);
    list_init(&tree->unused_links);
    return true;
}

static void destroy_group(void *ptr)
{
    list_destroy(ptr, NULL);
}

void bsp_tree_deinit(bsp_tree_t *tree)
{
    if (!tree)
        return;
    list_clear(&tree->groups, destroy_group);
    list_clear_free(&tree->links);
    list_clear_free(&tree->unused_links);
}

static bool add_to_group(list_t *group, bsp_t *bsp)
{
    bsp->group = group;
    return list_add_ptr(group, bsp);
}

static list_t *add_group(bsp_tree_t *tree)
{
    list_t *group = NULL;

    group = list_create();
    if (!group)
        return NULL;
    if (!list_add_ptr(&tree->groups, group)) {
        list_destroy(group, NULL);
        return NULL;
    }
    return group;
}

static bool merge_groups(list_t *dest, list_t *src)
{
    for (node_t *n = src->head; n; n = n->next) {
        if (!add_to_group(dest, n->data))
            return false;
    }
    return true;
}

static bool handle_group_merge(bsp_link_t *link, list_t **group, bsp_t **bsp)
{
    if (link->bsp1->group->size >= link->bsp2->group->size) {
        *group = link->bsp1->group;
        *bsp = link->bsp2;
        return merge_groups(link->bsp1->group, link->bsp2->group);
    }
    *group = link->bsp2->group;
    *bsp = link->bsp1;
    return merge_groups(link->bsp2->group, link->bsp1->group);
}

static void set_group_op(list_t **group, bsp_t **to_add, bsp_link_t *link)
{
    if (!link->bsp2->group) {
        *group = link->bsp1->group;
        *to_add = link->bsp2;
    } else if (!link->bsp1->group) {
        *group = link->bsp2->group;
        *to_add = link->bsp1;
    }
}

static bool process_link(bsp_tree_t *tree, bsp_link_t *link)
{
    list_t *group = NULL;
    bsp_t *to_add = NULL;

    if (!link->bsp1->group && !link->bsp2->group) {
        group = add_group(tree);
        if (!group || !add_to_group(group, link->bsp1))
            return false;
        to_add = link->bsp2;
    } else if (link->bsp1->group == link->bsp2->group) {
        return list_add_ptr(&tree->unused_links, link);
    } else if (link->bsp1->group && link->bsp2->group) {
        if (!handle_group_merge(link, &group, &to_add))
            return false;
    } else {
        set_group_op(&group, &to_add, link);
    }
    return add_to_group(group, to_add)
        && list_add_ptr(&tree->links, link);
}

static bool build_tree(bsp_tree_t *tree, bsp_nav_t *nav)
{
    bsp_link_t *link = NULL;
    int size = 0;

    if (!tree || !nav || nav->links.size <= 0)
        return false;
    size = nav->links.size;
    link = list_pop(&nav->links, rand() % nav->links.size);
    if (!link || !process_link(tree, link))
        return false;
    if (size <= 1)
        return true;
    return build_tree(tree, nav);
}

static bool add_cycles(bsp_tree_t *tree, bsp_t *bsp)
{
    bsp_link_t *link = NULL;
    int extra_nb = 0;

    extra_nb = tree->unused_links.size * bsp->c_settings.cycling_rate;
    for (int i = 0; i < extra_nb; i++) {
        link = list_pop(&tree->unused_links, rand() & tree->unused_links.size);
        if (!link)
            return false;
        if (!list_add_ptr(&tree->links, link)) {
            free(link);
            return false;
        }
    }
    return true;
}

bool bsp_generate_tree(bsp_tree_t *tree, bsp_t *bsp)
{
    bool status = true;
    bsp_nav_t nav = {0};

    if (!tree || !bsp)
        return false;
    bsp_nav_init(&nav);
    if (!bsp_nav_traverse(&nav, bsp)) {
        bsp_nav_deinit(&nav);
        return false;
    }
    status = build_tree(tree, &nav);
    bsp_nav_deinit(&nav);
    return status && add_cycles(tree, bsp);
}
