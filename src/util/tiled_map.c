#include <assert.h>
#include <stdio.h>
#include <math.h>
#include "tiled_map.h"
#include "../ecs/ecs.h"
#include "../util/types.h"


static void load_entity(const ECS* ecs, const Tile* tile) {
    switch (tile->objid) {
        case PlayerCharacterID:
            ecs_create_player(ecs, tile->x, tile->y);
            break;
        default:
            break;
    }
}

static void load_game_obj(const ECS* ecs, const Tile* tile, const char* image) {
    const entity_t e = ecs_create_sprite(ecs, tile->zindex, image);
    EntityTransform* transform = ecs_get_transform(ecs, e);
    transform->pos.x = tile->x;
    transform->pos.y = tile->y;
}


static void read_str(char* buffer, FILE* file, const size_t max_length) {
    char c;
    int i = 0;

    while (
        !feof(file)
        && fread(&c, sizeof(char), 1, file)
        && i < max_length
    ) {
        buffer[i++] = c;
        if (c == '\0') { break; }
    }
}


void load_tiled_map(const ECS* ecs, const char* path) {
    FILE* input = fopen(path, "rb");
    assert(input != NULL);

    int width, height;
    char buffer[256];

    // MAP WIDTH AND HEIGHT
    fread(&width, sizeof(int), 1, input);
    fread(&height, sizeof(int), 1, input);

    // GROUND IMAGE
    read_str(buffer, input, 256);
    ecs_create_ground_sprite(ecs, buffer);

    int coast_n;
    int coast_terrain;

    // Read objs
    while (!feof(input)) {
        Tile tile;
        int groupid, n;
        fread(&n, sizeof(int), 1, input);
        fread(&groupid, sizeof(int), 1, input);
        if (feof(input)) { return; }

        for (int i = 0; i < n && !feof(input); i++) {
            if (!fread(&tile, sizeof(Tile), 1, input)) {
                tile.x = roundf(tile.x);
                tile.y = roundf(tile.y);
                break;
            }

            switch (groupid) {
                case CoastGroupID:
                    fread(&coast_n, sizeof(int), 1, input);
                    fread(&coast_terrain, sizeof(int), 1, input);
                    break;
                case CollisionGroupID:
                    ecs_add_static_collision(ecs, tile.x, tile.y, tile.width, tile.height);
                    break;
                case EntitiesGroupID:
                    load_entity(ecs, &tile);
                    break;
                case GameObjsGroupID:
                    read_str(buffer, input, 256);
                    load_game_obj(ecs, &tile, buffer);
                    break;
                default:
                    break;

            };
        }
    }

    fclose(input);
}