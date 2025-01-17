#include "TiledMap.h"
#include <iostream>
#include <fstream>
#include "TexturePool.hpp"


typedef struct tile {
    float x;
    float y;
    float width;
    float height;
    int objId;
    int zindex;
} Tile;


static void load_character(pk::ECS* ecs, const Tile& tile) {
    const pk::entity_t e = ecs->entity_create(pk::CAMERA_ZINDEX_WORLD, tile.x, tile.y, true);
    pk::Transform& transform = ecs->get_transform(e);
    transform.size = {pk::CHARACTER_SIZE, pk::CHARACTER_SIZE};
    transform.pos = {tile.x - pk::CHARACTER_SIZE / 2.0f, tile.y - pk::CHARACTER_SIZE};

    switch (tile.objId) {
        case pk::PlayerID:
            ecs->add_component<pk::Player>(e, pk::Player{});
            ecs->add_component<pk::SpriteAnimation>(e, pk::SpriteAnimation{pk::PLAYER_SPRITE_ANIMATION});
            break;
        case pk::NurseID:
            break;
    }
}

static void load_coast(pk::ECS* ecs, const Tile& tile, const int coast_n, const int coast_terrain) {

}

static void load_water(pk::ECS* ecs, const Tile& tile) {
    // Create water entity
    const pk::entity_t e = ecs->entity_create(pk::CAMERA_ZINDEX_WATER, tile.x, tile.y, true);

    // Water tile
    const Image tile_img = LoadImageFromTexture(
        pk::gTexturePool.get(TILE_SETS_PATH "water/0.png")
    );

    // Water Rect
    Image img = GenImageColor(static_cast<int>(tile.width), static_cast<int>(tile.height), BLACK);
    float x = 0.0f;
    float y = 0.0f;

    const int rows = static_cast<int>(tile.height) / static_cast<int>(pk::TILE_SIZE);
    const int cols = static_cast<int>(tile.width) / static_cast<int>(pk::TILE_SIZE);

    // Fill water image
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            ImageDraw(
                &img,
                tile_img,
                Rectangle{0.0f, 0.0f, pk::TILE_SIZE, pk::TILE_SIZE},
                Rectangle{x, y, pk::TILE_SIZE, pk::TILE_SIZE},
                WHITE
            );
            x += pk::TILE_SIZE;
        }
        x = 0.0f;
        y += pk::TILE_SIZE;
    }

    // Create water component
    std::string water_texture_name{"tile-water-"};
    water_texture_name += std::to_string(tile.x);
    water_texture_name += '-';
    water_texture_name += std::to_string(tile.y);
    const Texture2D t = LoadTextureFromImage(img);
    pk::gTexturePool.register_texture(water_texture_name.c_str(), t);
    ecs->add_component(e, pk::Water(t));

    // Unload aux images
    UnloadImage(tile_img);
    UnloadImage(img);
}

static void load_transition(pk::ECS* ecs, const Tile& tile) {

}

static void load_collision(pk::ECS* ecs, const Tile& tile) {
    ecs->add_static_collision(tile.x, tile.y, tile.width, tile.height);
}

static void load_monster(pk::ECS* ecs, const Tile& tile) {

}

static void load_sprite(pk::ECS* ecs, const Tile& tile, const char* image_path) {
    const pk::entity_t e = ecs->sprite_create(
        pk::CAMERA_ZINDEX_WORLD,
        image_path,
        tile.x,
        tile.y
    );
}


void pk::read_tiled_map(const char *map_path, pk::ECS *ecs) {
    std::ifstream file(map_path);
    if (file.is_open() == false) {
        std::cout << "failed to open " << map_path << " map!\n";
        return;
    }

    int map_width, map_height, n, groupId;
    std::string str;
    Tile tile;

    file >> map_width;
    file >> map_height;
    file >> str;

    ecs->sprite_create(pk::CAMERA_ZINDEX_GROUND, str.c_str(), 0.0f, 0.0f);

    while (file >> str) {
        file >> n;
        file >> groupId;

        for (int i = 0; i < n; i++) {
            int cost_terrain;
            int coast_n;
            file >> tile.x >> tile.y >> tile.width >> tile.height >> tile.objId >> tile.zindex;

            switch (groupId) {
                case pk::CoastGroup:
                    file >> coast_n >> cost_terrain;
                    load_coast(ecs, tile, coast_n, cost_terrain);
                    break;
                case pk::SpriteGroup:
                    file >> str;
                    load_sprite(ecs, tile, str.c_str());
                    break;
                case pk::CharacterGroup:
                    load_character(ecs, tile);
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

    file.close();
}