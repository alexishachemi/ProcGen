#include <stdlib.h>
#include <raylib.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include "bsp.h"

static vec2_t screen_size = {800, 600};

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

static void draw_leaf(bsp_t *bsp)
{
    bsp_t *adj = NULL;
    vec2_t center = rect_center(bsp->rect);
    vec2_t adj_center = {0};

    draw_rect(bsp->room, WHITE);
    for (node_t *n = bsp->adjacents.head; n; n = n->next) {
        adj = n->data;
        adj_center = rect_center(adj->rect);
        DrawLine(center.x, center.y, adj_center.x, adj_center.y, RED);
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
}

static void generate(bsp_t **bsp_ptr)
{
    if (*bsp_ptr)
        bsp_destroy(*bsp_ptr);
    *bsp_ptr = bsp_create((rect_t){{0, 0}, vec2_sub_i(screen_size, 1)});
    bsp_set_split_info(*bsp_ptr, 4, 2.7f, 0);
    bsp_set_room_info(*bsp_ptr, 1.3f, 10, 20, 0.5);
    bsp_generate(*bsp_ptr);
}

static void display(bsp_t **bsp_ptr)
{
    bool pressed = false;

    InitWindow(screen_size.x, screen_size.y, "ProcGen - Debug");
    while (!WindowShouldClose()) {
        if (!pressed && IsKeyPressed(KEY_SPACE)) {
            pressed = true;
            generate(bsp_ptr);
        } else if (IsKeyReleased(KEY_SPACE)) {
            pressed = false;
        }
        BeginDrawing();
        ClearBackground(GRAY);
        draw_bsp(*bsp_ptr, 0);
        EndDrawing();
    }
    CloseWindow();
}

int main(void)
{
    bsp_t *bsp = NULL;

    generate(&bsp);
    display(&bsp);
    bsp_destroy(bsp);
    return 0;
}
