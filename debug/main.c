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

static Color cell_to_clr(cell_t cell, Color on, Color off)
{
    if (cell == C_ON || cell == C_ALWAYS_ON)
        return on;
    return off;
}

static void draw_automaton(automaton_t *a, Color on, Color off)
{
    for (int y = 0; y < a->size.y; y++) {
        for (int x = 0; x < a->size.x; x++) {
            DrawPixel(x, y, cell_to_clr(automaton_get(a, x, y), on, off));
        }
    }
}

static void draw_procgen(procgen_t *pg)
{
    // draw_bsp(&pg->bsp, 0);
    // draw_corridors(pg);
    draw_automaton(&pg->automaton, BLACK, WHITE);
}

static void generate(procgen_t *pg)
{
    if (pg->initialized)
        procgen_deinit(pg);
    procgen_init(pg);
    procgen_generate(pg, screen_size);
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
    procgen_t pg = {0};

    pg.split_settings = (bsp_split_settings_t) {
        .splits = 4,
        .max_ratio = 2.7,
        .same_split_percent = 0
    };
    pg.room_settings = (bsp_room_settings_t){
        .max_ratio = 1.3,
        .min_coverage_percent = 10,
        .max_coverage_percent = 20,
        .spacing_rate = 0.3
    };
    pg.corridor_settings = (bsp_corridor_settings_t){
        .room_link_min_touch = 10,
        .cycling_rate = 0.05
    };
    pg.automaton_settings = (automaton_settings_t){
        .iterations = 0,
        .noise_on_percent = 50,
        .cell_on_minimum_neighbors = 4,
        .corridor_inner_size = 1,
        .corridor_outer_size = 0,
        .room_outline_size = 10
    };
    generate(&pg);
    // display(&pg);
    procgen_deinit(&pg);
    return 0;
}
