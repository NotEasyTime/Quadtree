#include "quadtree.h"
#include <stdlib.h>
#include <stdio.h>

QuadTree* new_tree(Rectangle domain) {
    QuadTree *new_quad_tree = malloc(sizeof(QuadTree));
    if (new_quad_tree == NULL) {
        printf("MEM ALLOC FAILED");
        return NULL;
    }

    new_quad_tree->domain = domain;
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

void free_tree(QuadTree* qt) {
    if (qt == NULL) {
        return;
    }

    for (int i = 0; i < 4; i++) {
        if (qt->cardinal[i] != NULL) {
            free_tree(qt->cardinal[i]);
        }
    }

    free(qt);
}



void insert(QuadTree *qt, Rectangle rect) {
    // If the tree is not split and there's room for more items, just add the item.
    if (qt->top < 6 && qt->split == false) {
        qt->items[qt->top] = rect;
        qt->top++;
    } else {
        // If the node is full and needs to split.
        if (!qt->split) {
            qt->split = true;

            // Subdivide the parent node into 4 quadrants.
            subdivide(qt, NORTH_WEST);
            subdivide(qt, NORTH_EAST);
            subdivide(qt, SOUTH_WEST);
            subdivide(qt, SOUTH_EAST);

            // Move existing items into the appropriate child nodes.
            for (int i = 0; i < qt->top; i++) {
                if (qt->items[i].x < qt->domain.x + qt->domain.width / 2) {
                    if (qt->items[i].y < qt->domain.y + qt->domain.height / 2) {
                        insert(qt->cardinal[NORTH_WEST], qt->items[i]);
                    } else {
                        insert(qt->cardinal[SOUTH_WEST], qt->items[i]);
                    }
                } else {
                    if (qt->items[i].y < qt->domain.y + qt->domain.height / 2) {
                        insert(qt->cardinal[NORTH_EAST], qt->items[i]);
                    } else {
                        insert(qt->cardinal[SOUTH_EAST], qt->items[i]);
                    }
                }
            }

            // Clear the items in the parent node since they have been moved.
            qt->top = 0;
        }

        // After the split, we now add the new item to the appropriate child node.
        if (rect.x < qt->domain.x + qt->domain.width / 2) {
            if (rect.y < qt->domain.y + qt->domain.height / 2) {
                insert(qt->cardinal[NORTH_WEST], rect);
            } else {
                insert(qt->cardinal[SOUTH_WEST], rect);
            }
        } else {
            if (rect.y < qt->domain.y + qt->domain.height / 2) {
                insert(qt->cardinal[NORTH_EAST], rect);
            } else {
                insert(qt->cardinal[SOUTH_EAST], rect);
            }
        }
    }
}


void subdivide(QuadTree *parent, int direction){

    switch(direction){
        case(NORTH_WEST):
        parent->cardinal[NORTH_WEST] = new_tree((Rectangle){
            parent->domain.x,
            parent->domain.y,
            parent->domain.width / 2,
            parent->domain.height / 2
        });
        break;
        case(NORTH_EAST):
        parent->cardinal[NORTH_EAST] = new_tree((Rectangle){
            parent->domain.x + parent->domain.width / 2,
            parent->domain.y,
            parent->domain.width / 2,
            parent->domain.height / 2
        });
        break;
        case(SOUTH_WEST):
        parent->cardinal[SOUTH_WEST] = new_tree((Rectangle){
            parent->domain.x,
            parent->domain.y + parent->domain.height / 2,
            parent->domain.width / 2,
            parent->domain.height / 2
        });
        break;
        case(SOUTH_EAST):
        parent->cardinal[SOUTH_EAST] = new_tree((Rectangle){
            parent->domain.x + parent->domain.width / 2,
            parent->domain.y + parent->domain.height / 2,
            parent->domain.width / 2,
            parent->domain.height / 2
        });
        break;
    }


}

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
