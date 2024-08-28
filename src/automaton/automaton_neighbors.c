#include "automaton.h"

void automaton_get_cell_neihbors_pos(cell_nh_t nh, int x, int y)
{
    nh[0] = (vec2_t){x - 1, y};
    nh[1] = (vec2_t){x - 1, y - 1};
    nh[2] = (vec2_t){x - 1, y + 1};
    nh[3] = (vec2_t){x + 1, y};
    nh[4] = (vec2_t){x + 1, y - 1};
    nh[5] = (vec2_t){x + 1, y + 1};
    nh[6] = (vec2_t){x, y + 1};
    nh[7] = (vec2_t){x, y - 1};
}

int automaton_count_neighbors_on(automaton_t *a, int x, int y)
{
    int count = 0;
    cell_t cell;
    cell_nh_t nh = {0};

    automaton_get_cell_neihbors_pos(nh, x, y);
    for (int i = 0; i < CELL_NH_SIZE; i++) {
        cell = automaton_get(a, nh[i].x, nh[i].y);
        count += cell == C_ON || cell == C_ALWAYS_ON;
    }
    return count;
}
