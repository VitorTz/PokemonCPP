#ifndef TILED_MAP_H
#define TILED_MAP_H
#include "../ecs/ecs.h"


typedef struct _tile {
    float x;
    float y;
    float width;
    float height;
    int objid;
    int zindex;
} Tile;


void load_tiled_map(const ECS* ecs, const char* path);


#endif //TILED_MAP_H
