#include <stdlib.h>
#include <raylib.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include "bsp.h"

static vec2_t screen_size = {800, 600};

static Color COLORS[] = {
    RED, GREEN, BLUE, YELLOW, PURPLE, PINK, BLACK, WHITE
};

void draw_rect(rect_t r, Color color)
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

void draw_bsp(const bsp_t *bsp, int depth)
{
    if (!bsp)
        return;
    draw_rect(bsp->rect, COLORS[depth % (sizeof(COLORS) / sizeof(Color))]);
    draw_bsp(bsp->sub1, depth + 1);
    draw_bsp(bsp->sub2, depth + 1);
}

void split(bsp_t **bsp_ptr)
{
    if (*bsp_ptr)
        bsp_destroy(*bsp_ptr);
    *bsp_ptr = bsp_create((rect_t){{0, 0}, vec2_sub_i(screen_size, 1)});
    bsp_split(*bsp_ptr, 2.7f, 4, 10);
}

int main(void)
{
    bsp_t *bsp = NULL;
    bool pressed = false;

    InitWindow(screen_size.x, screen_size.y, "ProcGen - Debug");
    while (!WindowShouldClose()) {
        if (!pressed && IsKeyPressed(KEY_SPACE)) {
            pressed = true;
            split(&bsp);
        } else if (IsKeyReleased(KEY_SPACE))
            pressed = false;
        BeginDrawing();
        ClearBackground(GRAY);
        draw_bsp(bsp, 0);
        EndDrawing();
    }
    CloseWindow();
    bsp_destroy(bsp);
    return 0;
}
