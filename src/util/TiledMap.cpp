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
    printf("%d %d\n%s\n", width, height, buffer);

    int coast_n;
    int coast_terrain;

    // Read objs
    while (!feof(input)) {
        Tile tile{};
        int groupId, n;
        fread(&n, sizeof(int), 1, input);
        fread(&groupId, sizeof(int), 1, input);
        if (feof(input)) { return; }

        printf("%d %d\n", n, groupId);
        for (int i = 0; i < n && !feof(input); i++) {
            if (!fread(&tile, sizeof(Tile), 1, input)) {
                break;
            }
            printf("%.2f %.2f %.2f %.2f %d %d", tile.x, tile.y, tile.width, tile.height, tile.objId, tile.zindex);
            if (groupId == 1) {
                fread(&coast_n, sizeof(int), 1, input);
                fread(&coast_terrain, sizeof(int), 1, input);
                printf(" %d %d", coast_n, coast_terrain);
            }
            printf("\n");
        }
    }

    fclose(input);

}
