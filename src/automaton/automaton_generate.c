#include "automaton.h"

static int automaton_count_neighbors_on(automaton_t *a, int x, int y)
{
    int count = 0;
    cell_t cell;
    vec2_t neighbors[] = {
        {x - 1, y},
        {x - 1, y - 1},
        {x - 1, y + 1},
        {x + 1, y},
        {x + 1, y - 1},
        {x + 1, y + 1},
        {x, y + 1},
        {x, y - 1}
    };

    for (int i = 0; i < 8; i++) {
        cell = automaton_get(a, neighbors[i].x, neighbors[i].y);
        count += cell == C_ON || cell == C_ALWAYS_ON;
    }
    return count;
}

static bool automaton_copy(automaton_t *dest, automaton_t *src)
{
    if (!automaton_init(dest, src->size))
        return false;
    dest->settings = src->settings;
    for (int y = 0; y < src->size.y; y++) {
        for (int x = 0; x < src->size.x; x++) {
            automaton_set(dest, x, y,  automaton_get(src, x, y));
        }
    }
    return true;
}

static void process_cell(automaton_t *a, automaton_t *ref, int x, int y)
{
    int nh = 0;
    cell_t current_cell;
    cell_t cell;

    current_cell = automaton_get(ref, x, y);
    if (current_cell == C_ALWAYS_ON || current_cell == C_ALWAYS_OFF)
        return;
    nh = automaton_count_neighbors_on(ref, x, y);
    cell = nh >= a->settings.cell_on_minimum_neighbors ? C_ON : C_OFF;
    automaton_set(a, x, y, cell);
}

static bool generate(automaton_t *a, int iterations)
{
    automaton_t ref;

    if (iterations <= 0)
        return true;
    if (!a || !automaton_copy(&ref, a))
        return false;
    for (int y = 0; y < a->size.y; y++) {
        for (int x = 0; x < a->size.x; x++) {
            process_cell(a, &ref, x, y);
        }
    }
    automaton_deinit(&ref);
    return generate(a, iterations - 1);
}

bool automaton_generate(automaton_t *a)
{
    return automaton_add_noise(a) && generate(a, a->settings.iterations);
}
