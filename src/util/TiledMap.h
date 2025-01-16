#ifndef TILEDMAP_H
#define TILEDMAP_H
#include "../ecs/ECS.hpp"


namespace pk {

    void read_tiled_map(const char* map_path, pk::ECS * ecs);

}

#endif //TILEDMAP_H
