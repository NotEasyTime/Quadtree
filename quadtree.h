#ifndef GP_QTREE_
#define GP_QTREE_

#define NORTH_WEST 0
#define NORTH_EAST 1
#define SOUTH_WEST 2
#define SOUTH_EAST 3

#include "/Users/parry/raylib/src/raylib.h"

typedef struct QuadTree{

    Rectangle domain;
    int top, capacity;
    Rectangle items[7];
    bool split;

    struct QuadTree *cardinal[4];

}QuadTree;

void insert(QuadTree*, Rectangle);
void subdivide(QuadTree*, int);
QuadTree* new_tree(Rectangle);
void free_tree(QuadTree*);
void draw_tree(QuadTree*);

#endif
