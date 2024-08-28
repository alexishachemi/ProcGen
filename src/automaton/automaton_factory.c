#include <string.h>
#include <stdlib.h>
#include "automaton.h"

bool automaton_init(automaton_t *a, vec2_t size)
{
    if (!a)
        return false;
    a->size = size;
    a->map = malloc(sizeof(cell_t*) * (size.y + 1));
    if (!a->map)
        return false;
    memset(a->map, 0, sizeof(cell_t*) * (size.y + 1));
    for (int i = 0; i < size.y; i++) {
        a->map[i] = malloc(sizeof(cell_t) * (size.x + 1));
        if (!a->map[i]) {
            automaton_deinit(a);
            return false;
        }
        memset(a->map[i], 0, sizeof(cell_t) * (size.x + 1));
    }
    return true;
}

void automaton_deinit(automaton_t *a)
{
    if (!a || !a->map)
        return;
    for (int i = 0; a->map[i]; i++)
        free(a->map[i]);
    free(a->map);
    a->map = NULL;
}
