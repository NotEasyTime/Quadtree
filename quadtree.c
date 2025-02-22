#include "quadtree.h"
#include <stdlib.h>
#include <stdio.h>

QuadTree* new_tree() {
    QuadTree *new_quad_tree = malloc(sizeof(QuadTree));
    if (new_quad_tree == NULL) {
        printf("MEM ALLOC FAILED");
        return NULL;
    }

    new_quad_tree->domain = (Rectangle){0, 0, 100, 100};
    new_quad_tree->top = 0;
    new_quad_tree->capacity = 100;
    for (int i = 0; i < 7; i++) {
        new_quad_tree->items[i] = (Rectangle){0, 0, 0, 0};
    }
    new_quad_tree->split = false;
    for (int i = 0; i < 4; i++) {
        new_quad_tree->cardinal[i] = NULL;
    }
    return new_quad_tree;
}


void insert(QuadTree *qt, Rectangle rect){
    if( qt->top < 6 && qt->split == false ){
        qt->items[qt->top] = rect;
        qt->top++;
    } else {
        qt->split = true;
        for( int i = 0; i < qt->top; ++i ){
            if(qt->items[i].x < qt->domain.x + (qt->domain.width / 2) &&
                qt->items[i].y < qt->domain.y + (qt->domain.height / 2)){
                    printf("NORTH_WEST");
            }
            if(qt->items[i].x > qt->domain.x + (qt->domain.width / 2) &&
                qt->items[i].y < qt->domain.y + (qt->domain.height / 2)){
                    printf("NORTH_EAST");
            }
            if(qt->items[i].x < qt->domain.x + (qt->domain.width / 2) &&
                qt->items[i].y > qt->domain.y + (qt->domain.height / 2)){
                    printf("SOUTH_WEST");
            }
            if(qt->items[i].x > qt->domain.x + (qt->domain.width / 2) &&
                qt->items[i].y > qt->domain.y + (qt->domain.height / 2)){
                    printf("SOUTH_EAST");
            }
        }
    }
}

void subdivide(QuadTree *parent){

}
