#include "automaton.h"

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

static bool switch_off_by_nh_count(automaton_t *a, int count)
{
    automaton_t ref;
    
    if (!automaton_copy(&ref, a))
        return false;
    for (int y = 0; y < a->size.y; y++) {
        for (int x = 0; x < a->size.x; x++) {
            if (automaton_get(&ref, x, y) != C_ON)
                continue;
            if (automaton_count_neighbors_on(&ref, x, y) == count)
                automaton_set(a, x, y, C_OFF);
        }
    }
    automaton_deinit(&ref);
    return true;
}

static void process_cell(automaton_t *a, automaton_t *ref, int x, int y)
{
    int nh = 0;
    cell_t current_cell;
    cell_t cell;

    current_cell = automaton_get(ref, x, y);
    if (automaton_c_constant(current_cell))
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
    if (!generate(a, a->settings.iterations))
        return false;
    if (a->settings.apply_flood_fill && !automaton_flood_fill(a))
        return false;
    return switch_off_by_nh_count(a, 3)
        && switch_off_by_nh_count(a, 2)
        && switch_off_by_nh_count(a, 1);
}
