#include <stdio.h>
#include "utils.h"
#include "bsp.h"
#include "rect.h"

rect_t rect_new_i(int x, int y, int w, int h)
{
    return (rect_t){(vec2_t){x, y}, (vec2_t){w, h}};
}

void rect_print(rect_t r)
{
    printf("(p: (%d, %d), s: (%d, %d))", r.pos.x, r.pos.y, r.size.x, r.size.y);
}

int rect_touching_overlap(rect_t r1, rect_t r2)
{
    int x1 = r1.pos.x;
    int y1 = r1.pos.y;
    int w1 = r1.size.x;
    int h1 = r1.size.y;
    int x2 = r2.pos.x;
    int y2 = r2.pos.y;
    int w2 = r2.size.x;
    int h2 = r2.size.y;
    int overlap = 0;

    if (x1 + w1 == x2 || x2 + w2 == x1)
        overlap = min(y1 + h1, y2 + h2) - max(y1, y2);
    else if (y1 + h1 == y2 || y2 + h2 == y1)
        overlap = min(x1 + w1, x2 + w2) - max(x1, x2);
    return max(overlap, 0);
}

static bool get_v_centers(rect_t r1, rect_t r2,
    vec2_t *c1, vec2_t *c2)
{
    int start1, start2, end1, end2, min_val, max_val, center;

    start1 = r1.pos.y;
    end1 = r1.pos.y + r1.size.y;
    start2 = r2.pos.y;
    end2 = r2.pos.y + r2.size.y;
    min_val = max(start1, start2);
    max_val = min(end1, end2);
    if (max_val - min_val <= 0)
        return false;
    center = min_val + ((max_val - min_val) / 2);
    c1->y = center;
    c2->y = center;
    if (r1.pos.x < r2.pos.x) {
        c1->x = r1.pos.x + r1.size.x;
        c2->x = r2.pos.x;
    } else {
        c1->x = r1.pos.x;
        c2->x = r2.pos.x + r2.size.x;
    }
    return true;
}

static bool get_h_centers(rect_t r1, rect_t r2,
    vec2_t *c1, vec2_t *c2)
{
    int start1, start2, end1, end2, min_val, max_val, center;

    start1 = r1.pos.x;
    end1 = r1.pos.x + r1.size.x;
    start2 = r2.pos.x;
    end2 = r2.pos.x + r2.size.x;
    min_val = max(start1, start2);
    max_val = min(end1, end2);
    if (max_val - min_val <= 0)
        return false;
    center = min_val + ((max_val - min_val) / 2);
    c1->x = center;
    c2->x = center;
    if (r1.pos.y < r2.pos.y) {
        c1->y = r1.pos.y + r1.size.y;
        c2->y = r2.pos.y;
    } else {
        c1->y = r1.pos.y;
        c2->y = r2.pos.y + r2.size.y;
    }
    return true;
}

bool rect_get_overlap_centers(rect_t r1, rect_t r2, vec2_t *c1, vec2_t *c2)
{
    if (!c1 || !c2)
        return false;
    return get_h_centers(r1, r2, c1, c2) || get_v_centers(r1, r2, c1, c2);
}

orient_t rect_get_overlap_orientation(rect_t r1, rect_t r2)
{
    int x1 = r1.pos.x;
    int y1 = r1.pos.y;
    int w1 = r1.size.x;
    int h1 = r1.size.y;
    int x2 = r2.pos.x;
    int y2 = r2.pos.y;
    int w2 = r2.size.x;
    int h2 = r2.size.y;

    if ((x1 + w1 == x2 || x2 + w2 == x1) && (y1 < y2 + h2 && y1 + h1 > y2))
        return O_VERTICAL;
    if ((y1 + h1 == y2 || y2 + h2 == y1) && (x1 < x2 + w2 && x1 + w1 > x2))
        return O_HORIZONTAL;
    return O_NONE;
}
