#include "automaton.h"

static bool is_visitable(automaton_t *a, automaton_t *fmap, vec2_t pos)
{
    cell_t cell;

    if (!automaton_pos_is_valid(a, pos.x, pos.y))
        return false;
    cell = automaton_get(a, pos.x, pos.y);
    return (cell == C_OFF || cell == C_ALWAYS_OFF)
        && automaton_get(fmap, pos.x, pos.y) != C_ON;
}

static bool is_connected(automaton_t *a, vec2_t pos)
{
    return automaton_get(a, pos.x,pos.y) == C_ALWAYS_OFF;
}

static bool visit(automaton_t *a, automaton_t *fmap, list_t *to_visit, vec2_t pos)
{
    cell_nh_t nh = {0};

    automaton_set(fmap, pos.x, pos.y, C_ON);
    automaton_get_cell_neihbors_pos(nh, pos.x, pos.y);
    for (int i = 0; i < CELL_NH_SIZE; i++) {
        if (!is_visitable(a, fmap, nh[i]))
            continue;
        if (!list_add_copy(to_visit, nh + i, sizeof(vec2_t)))
            return false;
    }
    return true;
}

static bool populate_fill(automaton_t *a, automaton_t *fmap,
    automaton_fill_t *fill, list_t *to_visit)
{
    vec2_t *pos = NULL;

    while (to_visit->head) {
        pos = list_pop(to_visit, 0);
        if (!is_visitable(a, fmap, *pos)) {
            free(pos);
            continue;
        }
        if (!visit(a, fmap, to_visit, *pos)) {
            free(pos);
            return false;
        }
        if (!list_add_copy(&fill->cells, pos, sizeof(vec2_t))) {
            free(pos);
            return false;
        }
        if (fill->state != A_CONNECTED && is_connected(a, *pos))
            fill->state = A_CONNECTED;
        free(pos);
    }
    return true;
}

static void *alloc_fill()
{
    automaton_fill_t *fill = NULL;

    fill = malloc(sizeof(automaton_fill_t));
    if (!fill)
        return NULL;
    fill->state = A_ISOLATED;
    list_init(&fill->cells);
    return fill;
}

static bool new_fill(automaton_t *a, automaton_t *fmap, list_t *fills, vec2_t pos)
{
    automaton_fill_t *fill = NULL;
    list_t to_visit = {0};
    bool status = true;

    fill = list_add(fills, alloc_fill);
    if (!fill)
        return false;
    list_init(&to_visit);
    if (!list_add_copy(&to_visit, &pos, sizeof(vec2_t)))
        return false;
    status = populate_fill(a, fmap, fill, &to_visit);
    list_clear_free(&to_visit);
    return status;
}

static bool scan_fill(automaton_t *a, automaton_t *fmap, list_t *fills)
{
    vec2_t pos = {0};

    for (int y = 0; y < a->size.y; y++) {
        for (int x = 0; x < a->size.x; x++) {
            pos = (vec2_t){x, y};
            if (!is_visitable(a, fmap, pos))
                continue;
            if (!new_fill(a, fmap, fills, pos))
                return false;
        }
    }
    return true;
}

static void free_fill(automaton_fill_t *fill)
{
    if (!fill)
        return;
    list_clear_free(&fill->cells);
    free(fill);
}

static void apply_fills(automaton_t *a, list_t *fills)
{
    automaton_fill_t *f = NULL;
    vec2_t *pos = NULL;

    for (node_t *nf = fills->head; nf; nf = nf->next) {
        f = nf->data;
        if (f->state != A_ISOLATED)
            continue;
        for (node_t *n = f->cells.head; n; n = n->next) {
            pos = n->data;
            automaton_set(a, pos->x, pos->y, C_ON);
        }
    }
}

bool automaton_flood_fill(automaton_t *a)
{
    list_t fills;
    automaton_t fmap;
    bool status = true;

    if (!a)
        return false;
    list_init(&fills);
    if (!automaton_init(&fmap, a->size))
        return false;
    status = scan_fill(a, &fmap, &fills);
    if (status)
        apply_fills(a, &fills);
    list_clear(&fills, (callback_t)free_fill);
    automaton_deinit(&fmap);
    return status;
}
