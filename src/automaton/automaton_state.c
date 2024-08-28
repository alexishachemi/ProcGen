#include "stdlib.h"
#include "automaton.h"

static bool valid_pos(automaton_t *a, int x, int y)
{
    return x >= 0 && x < a->size.x && y >= 0 && y < a->size.y;
}

bool automaton_set(automaton_t *a, int x, int y, cell_t state)
{
    if (!a || !valid_pos(a, x, y))
        return false;
    a->map[y][x] = state;
    return true;
}

cell_t automaton_get(automaton_t *a, int x, int y)
{
    if (!a || !valid_pos(a, x, y))
        return C_OFF;
    return a->map[y][x];
}

static cell_t random_cell(int on_percent)
{
    return rand() % 100 < on_percent ? C_ON : C_OFF;
}

bool automaton_add_noise(automaton_t *a)
{
    cell_t cell;

    if (!a)
        return false;
    for (int y = 0; y < a->size.y; y++) {
        for (int x = 0; x < a->size.x; x++) {
            cell = automaton_get(a, x, y);
            if (cell == C_ALWAYS_OFF || cell == C_ALWAYS_ON)
                continue;
            automaton_set(a, x, y,
                random_cell(a->settings.noise_on_percent));
        }
    }
    return true;
}

bool automaton_c_constant(cell_t cell)
{
    return cell == C_ALWAYS_ON || cell == C_ALWAYS_OFF;
}
