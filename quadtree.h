#ifndef GP_QTREE_
#define GP_QTREE_

#define NORTH_WEST 1
#define NORTH_EAST 2
#define SOUTH_WEST 3
#define SOUTH_EAST 4

#include "/Users/parry/raylib/src/raylib.h"

typedef struct QuadTree{

    Rectangle domain;
    int top, capacity;
    Rectangle items[7];
    bool split;

    struct QuadTree *cardinal[4];

}QuadTree;

void insert(QuadTree*, Rectangle);
void subdivide(QuadTree*);
QuadTree* new_tree();

#endif
