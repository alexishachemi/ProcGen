#include "utils.h"

bool list_add_list(list_t *dest, list_t *src)
{
    if (!dest || !src)
        return false;
    for (node_t *n = src->head; n; n = n->next) {
        if (!list_add_ptr(dest, n->data))
            return false;
    }
    return true;
}
