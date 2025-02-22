#include <stdio.h>
#include <stdlib.h>
#include "/Users/parry/raylib/src/raylib.h"
#include "quadtree.h"

void draw_tree(QuadTree* qt) {

    // Draw the boundary of the current node
    DrawLine(qt->domain.x, qt->domain.y, qt->domain.x + qt->domain.width, qt->domain.y, BLACK); // Top line
    DrawLine(qt->domain.x, qt->domain.y, qt->domain.x, qt->domain.y + qt->domain.height, BLACK); // Left line
    DrawLine(qt->domain.x + qt->domain.width, qt->domain.y, qt->domain.x + qt->domain.width, qt->domain.y + qt->domain.height, BLACK); // Right line
    DrawLine(qt->domain.x, qt->domain.y + qt->domain.height, qt->domain.x + qt->domain.width, qt->domain.y + qt->domain.height, BLACK); // Bottom line

    if (!qt->split) {
        for (int i = 0; i < qt->top; i++) {
            DrawRectangle(qt->items[i].x, qt->items[i].y, qt->items[i].width, qt->items[i].height, BLUE);
        }
    }

    if (qt->cardinal[NORTH_WEST]) {
        draw_tree(qt->cardinal[NORTH_WEST]);
    }
    if (qt->cardinal[NORTH_EAST]) {
        draw_tree(qt->cardinal[NORTH_EAST]);
    }
    if (qt->cardinal[SOUTH_WEST]) {
        draw_tree(qt->cardinal[SOUTH_WEST]);
    }
    if (qt->cardinal[SOUTH_EAST]) {
        draw_tree(qt->cardinal[SOUTH_EAST]);
    }
}


int main(){

    unsigned int screen_width = 800;
    unsigned int screen_height = 800;

    InitWindow(screen_width, screen_height, "QuadTree");

    QuadTree *test = new_tree((Rectangle){0,0,screen_width,screen_height});

    while(!WindowShouldClose()){

        if(IsMouseButtonPressed(0)){
            insert(test,(Rectangle){GetMouseX(), GetMouseY(), 5,5});
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        draw_tree(test);

        EndDrawing();
    }

    free_tree(test);

    CloseWindow();
}
