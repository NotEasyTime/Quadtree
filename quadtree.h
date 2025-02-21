#ifndef GP_QTREE_
#define GP_QTREE_

#include "raylib.h"

typedef struct QuadTree{

    Rectangle domain;
    int capacity;
    Rectangle stored[7];

    struct QuadTree *north_west;
    struct QuadTree *north_east;
    struct QuadTree *south_west;
    struct QuadTree *south_east;

}QuadTree;

void insert(QuadTree*, Rectangle);
void subdivide(QuadTree*);

#endif
