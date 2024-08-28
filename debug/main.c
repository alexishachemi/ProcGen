#include <stdlib.h>
#include <raylib.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include "procgen.h"
#include "utils.h"

static vec2_t screen_size = {800, 600};


static void draw_line(vec2_t from, vec2_t to, Color color)
{
    DrawLine(from.x, from.y, to.x, to.y, color);
}

static void draw_rect_lines(rect_t r, Color color)
{
    vec2_t end = rect_end(r);

    for (int x = r.pos.x; x <= end.x; x++) {
        DrawPixel(x, r.pos.y, color);
        DrawPixel(x, end.y, color);
    }
    for (int y = r.pos.y; y <= end.y; y++) {
        DrawPixel(r.pos.x, y, color);
        DrawPixel(end.x, y, color);
    }
}

static void draw_rect(rect_t r, Color color)
{
    DrawRectangle(r.pos.x, r.pos.y, r.size.x, r.size.y, color);
}

static void draw_point(vec2_t pos, int size, Color color)
{
    draw_rect((rect_t){vec2_sub_i(pos, size / 2), (vec2_t){size, size}}, color);
}

static void draw_sized_line(vec2_t from, vec2_t to, int size, Color color)
{
    vec2_t current = from;

    while (current.x != to.x || current.y != to.y) {
        current.x += clamp((to.x - current.x) * -1, -1, 1);
        current.y += clamp((to.y - current.y) * -1, -1, 1);
        draw_point(current, size, color);
    }
    draw_point(current, size, color);
}

static void draw_leaf(bsp_t *bsp)
{
    // bsp_t *adj = NULL;
    // vec2_t center = rect_center(bsp->room);
    // vec2_t adj_center = {0};

    draw_rect(bsp->room, WHITE);
    // for (node_t *n = bsp->adjacents.head; n; n = n->next) {
    //     adj = n->data;
    //     adj_center = rect_center(adj->room);
    //     draw_line(center, adj_center, RED);
    // }
}

void draw_tree(bsp_tree_t *tree)
{
    bsp_link_t *bsp_link = NULL;

    for (node_t *n = tree->links.head; n; n = n->next) {
        bsp_link = n->data;
        draw_line(
            rect_center(bsp_link->bsp1->room),
            rect_center(bsp_link->bsp2->room),
            BLUE
        );
    }
}

static void draw_bsp(bsp_t *bsp, int depth)
{
    if (!bsp)
        return;
    draw_rect_lines(bsp->rect, GREEN);
    if (bsp_is_leaf(bsp)) {
        draw_leaf(bsp);
        return;
    }
    draw_bsp(bsp->sub1, depth + 1);
    draw_bsp(bsp->sub2, depth + 1);
    // if (depth <= 0)
    //     draw_tree(&bsp->tree);
}

static void draw_corridors(procgen_t *pg)
{
    segment_t *seg = NULL;

    for (node_t *n = pg->corridor_segments.head; n; n = n->next) {
        seg = n->data;
        draw_line(seg->a, seg->b, BROWN);
    }
}

static void draw_procgen(procgen_t *pg)
{
    draw_bsp(pg->bsp, 0);
    draw_corridors(pg);
}

static void generate(procgen_t *pg)
{
    if (pg->bsp)
        bsp_destroy(pg->bsp);
    list_clear_free(&pg->corridor_segments);
    pg->bsp = bsp_create((rect_t){{0, 0}, vec2_sub_i(screen_size, 1)});
    bsp_set_split_settings(pg->bsp, 4, 2.7f, 0);
    bsp_set_room_settings(pg->bsp, 1.3f, 10, 20, 0.3);
    bsp_set_corridor_settings(pg->bsp, 10, 0.05);
    procgen_generate(pg);
}

static void display(procgen_t *pg)
{
    bool pressed = false;

    InitWindow(screen_size.x, screen_size.y, "ProcGen - Debug");
    while (!WindowShouldClose()) {
        if (!pressed && IsKeyPressed(KEY_SPACE)) {
            pressed = true;
            generate(pg);
        } else if (IsKeyReleased(KEY_SPACE)) {
            pressed = false;
        }
        BeginDrawing();
        ClearBackground(GRAY);
        draw_procgen(pg);
        EndDrawing();
    }
    CloseWindow();
}

int main(void)
{
    procgen_t pg;

    procgen_init(&pg);
    generate(&pg);
    // display(&pg);
    procgen_deinit(&pg);
    return 0;
}
