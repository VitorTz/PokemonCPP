#include "TiledMap.h"
#include <stdio.h>


typedef struct _tile {
    float x;
    float y;
    float width;
    float height;
    int objId;
    int zindex;
} Tile;


static void load_character(pk::ECS* ecs, const Tile& tile) {

}

static void load_coast(pk::ECS* ecs, const Tile& tile, FILE* file) {
    int coast_n, coast_terrain;
    fread(&coast_n, sizeof(int), 1, file);
    fread(&coast_terrain, sizeof(int), 1, file);
}

static void load_water(pk::ECS* ecs, const Tile& tile) {

}

static void load_transition(pk::ECS* ecs, const Tile& tile) {

}

static void load_collision(pk::ECS* ecs, const Tile& tile) {
    ecs->add_static_collision(tile.x, tile.y, tile.width, tile.height);
}

static void load_monster(pk::ECS* ecs, const Tile& tile) {

}

static void load_sprite(pk::ECS* ecs, const Tile& tile) {

}

void pk::read_tiled_map(const char *map_path, pk::ECS *ecs) {
    FILE* input = fopen(map_path, "rb");

    if (input == nullptr) {
        printf("map file open fail. Map -> %s\n", map_path);
        return;
    }

    int width, height;
    int buffer_i = 0;
    char buffer[256];

    // Read width, height and ground image
    fread(&width, sizeof(int), 1, input);
    fread(&height, sizeof(int), 1, input);

    char c;
    while (!feof(input) && fread(&c, sizeof(char), 1, input)) {
        buffer[buffer_i++] = c;
        if (c == '\0') { break; }
    }

    // GROUND
    ecs->sprite_create(pk::CAMERA_ZINDEX_GROUND, buffer, 0.0f, 0.0f);

    // Read objs
    while (!feof(input)) {
        Tile tile{};
        int groupId, n;
        fread(&n, sizeof(int), 1, input);
        fread(&groupId, sizeof(int), 1, input);

        if (feof(input)) {
            return;
        }

        for (int i = 0; i < n && !feof(input); i++) {

            if (!fread(&tile, sizeof(Tile), 1, input)) {
                break;
            }

            switch (groupId) {
                case pk::CharacterGroup:
                    load_character(ecs, tile);
                    break;
                case pk::CoastGroup:
                    load_coast(ecs, tile, input);
                    break;
                case pk::MonsterGroup:
                    load_monster(ecs, tile);
                    break;
                case pk::SpriteGroup:
                    load_sprite(ecs, tile);
                    break;
                case pk::TransitionGroup:
                    load_transition(ecs, tile);
                    break;
                case pk::CollisionGroup:
                    load_collision(ecs, tile);
                    break;
                case pk::WaterGroup:
                    load_water(ecs, tile);
                    break;
                default:
                    break;
            }

        }
    }

    fclose(input);

}