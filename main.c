#include <stdio.h>
#include <stdlib.h>
#include "/Users/parry/raylib/src/raylib.h"
#include "quadtree.h"

int main(){
    InitWindow(800, 800, "QuadTree");

    QuadTree *test = new_tree();

    while(!WindowShouldClose()){

        BeginDrawing();
        ClearBackground(RAYWHITE);
        EndDrawing();
    }

    free(test);

    CloseWindow();
}
