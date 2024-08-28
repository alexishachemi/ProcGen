#include "procgen.h"
#include "utils.h"

bool automaton_draw_rect(automaton_t *a, rect_t rect, cell_t cell)
{
    vec2_t end = {0};

    if (!a)
        return false;
    end = rect_end(rect);
    for (int y = rect.pos.y; y < end.y; y++) {
        for (int x = rect.pos.x; x < end.x; x++) {
            if (!automaton_set(a, rect.pos.x, rect.pos.y, cell))
                return false;
        }
    }
    return true;
}

bool automaton_draw_point(automaton_t *a, vec2_t pos,
    cell_t inner_cell, int inner_size, cell_t outer_cell, int outer_size)
{
    int size = 0;
    cell_t cell;

    if (!a)
        return false;
    size = inner_size + outer_size;
    for (int y = pos.y - size; y <= pos.y + size; y++) {
        for (int x = pos.x - size; x <= pos.x + size; x++) {
            cell = outer_cell;
            if (x > pos.x - inner_size && x < pos.x + inner_size
                && y > pos.y - inner_size && y < pos.y + inner_size)
                cell = inner_cell;
            automaton_set(a, x, y, cell);
        }
    }
    return true;
}

bool automaton_draw_line(automaton_t *a, segment_t *s,
    cell_t inner_cell, int inner_size, cell_t outer_cell, int outer_size)
{
    vec2_t current = {0};
    
    if (!a)
        return false;
    current = s->a;
    while (current.x != s->b.x || current.y != s->b.y) {
        if (!automaton_draw_point(a, current,
            inner_cell, inner_size, outer_cell, outer_size))
            return false;
        current = vec2_move_towards(current, s->b, 1);
    }
    return automaton_draw_point(a, current, inner_cell, inner_size,
        outer_cell, outer_size);
}

bool automaton_draw_corridors(automaton_t *a, list_t *segments)
{
    if (!a || !segments)
        return false;
    for (node_t *n = segments->head; n; n = n->next) {
        if (!automaton_draw_line(
            a, n->data, 
            C_ALWAYS_OFF, a->settings.corridor_inner_size,
            C_OFF, a->settings.corridor_outer_size))
            return false;
    }
    return true;
}

static bool draw_bsp(automaton_t *a, bsp_t *bsp)
{
    if (!a || !bsp)
        return false;
    return true;
}

bool automaton_draw_bsp_zones(automaton_t *a, list_t *zones)
{
    if (!a || !zones)
        return false;
    for (node_t *n = zones->head; n; n = n->next) {
        if (!draw_bsp(a, n->data))
            return false;
    }
    return true;
}
