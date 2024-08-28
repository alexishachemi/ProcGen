#include <math.h>
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
            if (!automaton_set(a, x, y, cell))
                return false;
        }
    }
    return true;
}

bool automaton_draw_point(automaton_t *a, vec2_t pos, cell_t cell, int size)
{
    if (!a)
        return false;
    for (int y = pos.y - size; y <= pos.y + size; y++) {
        for (int x = pos.x - size; x <= pos.x + size; x++) {
            if (automaton_get(a, x, y) == C_ALWAYS_OFF)
                continue;
            automaton_set(a, x, y, cell);
        }
    }
    return true;
}

bool automaton_draw_line(automaton_t *a, segment_t *s, cell_t cell, int size)
{
    vec2_t current = {0};
    
    if (!a)
        return false;
    if (size <= 0)
        return 0;
    current = s->a;
    while (current.x != s->b.x || current.y != s->b.y) {
        if (!automaton_draw_point(a, current, cell, size))
            return false;
        current = vec2_move_towards(current, s->b, 1);
    }
    return automaton_draw_point(a, current, cell, size);
}

bool automaton_draw_corridors(automaton_t *a, list_t *segments)
{
    int inner, outer = 0;

    if (!a || !segments)
        return false;
    inner = a->settings.corridor_inner_size;
    outer = a->settings.corridor_outer_size;
    for (node_t *n = segments->head; n; n = n->next) {
        if (outer && !automaton_draw_line(a, n->data, C_OFF, inner + outer))
            return false;
        if (!automaton_draw_line(a, n->data, C_ALWAYS_OFF, inner))
            return false;
    }
    return true;
}

static bool draw_bsp_outline(automaton_t *a, bsp_t *bsp)
{
    int size = a->settings.room_outline_size;
    rect_t rect = bsp->rect;
    vec2_t pos = rect.pos;
    vec2_t end = {0};
    rect_t r = {0};

    end = rect_end(bsp->rect);
    r = (rect_t){pos, {rect.size.x, size}};
    if (!automaton_draw_rect(a, r, C_ALWAYS_ON))
        return false;
    r = (rect_t){{pos.x, end.y - size}, {rect.size.x, size}};
    if (!automaton_draw_rect(a, r, C_ALWAYS_ON))
        return false;
    r = (rect_t){pos, {size, rect.size.y}};
    if (!automaton_draw_rect(a, r, C_ALWAYS_ON))
        return false;
    r = (rect_t){{end.x - size, pos.y}, {size, rect.size.y}};
    return automaton_draw_rect(a, r, C_ALWAYS_ON);
}

static bool draw_bsp(automaton_t *a, bsp_t *bsp)
{
    return draw_bsp_outline(a, bsp)
        && automaton_draw_rect(a, bsp->room, C_ALWAYS_OFF);
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
