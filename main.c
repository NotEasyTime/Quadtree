#include <stdio.h>
#include <stdlib.h>
#include "/Users/parry/raylib/src/raylib.h"
#include "quadtree.h"

int main(){

    unsigned int screen_width = 800;
    unsigned int screen_height = 800;

    InitWindow(screen_width, screen_height, "QuadTree");

    QuadTree *test = new_tree((Rectangle){0,0,screen_width,screen_height});

    while(!WindowShouldClose()){

        if(IsMouseButtonPressed(0)){
            insert(test,(Rectangle){GetMouseX(), GetMouseY(), 5,5});
        }

        if(IsMouseButtonPressed(1)){
            remove_item(test, GetMousePosition());
        }


        BeginDrawing();
        ClearBackground(RAYWHITE);

        draw_tree(test);

        EndDrawing();
    }

    free_tree(test);

    CloseWindow();
}
