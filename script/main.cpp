#include <iostream>
#include <fstream>
#include <stdio.h>
#include <assert.h>
#include <string>


typedef struct _tile {
    float x;
    float y;
    float width;
    float height;
    int objid;
    int zindex;
} Tile;


void read_tiledmap(const char* map_path) {
    FILE* input = fopen(map_path, "rb");
    assert(input != NULL);

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

    printf("%d %d\n%s\n", width, height, buffer);

    int coast_n;
    int coast_terrain;

    // Read objs
    while (!feof(input)) {
        Tile tile{};
        int groupid, n;
        fread(&n, sizeof(int), 1, input);
        fread(&groupid, sizeof(int), 1, input);
        if (feof(input)) { return; }
        printf("%d %d\n", n, groupid);        
        for (int i = 0; i < n && !feof(input); i++) {
            if (!fread(&tile, sizeof(Tile), 1, input)) {
                break;
            }
            printf("%.2f %.2f %.2f %.2f %d %d", tile.x, tile.y, tile.width, tile.height, tile.objid, tile.zindex);
            if (groupid == 1) {
                fread(&coast_n, sizeof(int), 1, input);
                fread(&coast_terrain, sizeof(int), 1, input);
                printf(" %d %d", coast_n, coast_terrain);
            }
            printf("\n");
        }
    }

    fclose(input);
}

void txt_to_bin(const char* input_path, const char* output_path) {
    FILE* output = fopen(output_path, "wb");
    assert(output != NULL);

    std::ifstream file(input_path);
    assert(file.is_open());
    
    int a;
    std::string str;
    
    // Write width
    file >> str;
    printf("%s\n", str.c_str());    
    a = std::stoi(str);
    printf("%d\n", a);
    fwrite(&a, sizeof(int), 1, output);

    // Write height
    file >> str;
    printf("%s\n", str.c_str());
    a = std::stoi(str);
    fwrite(&a, sizeof(int), 1, output);
    printf("%d\n", a);    

    // Write ground image
    file >> str;
    const char* s = str.c_str();
    printf("%s\n", str.c_str());    
    fwrite(s, sizeof(char), str.size() + 1, output);

    int n;
    int groupid;
    Tile tile;

    int coast_n;
    int cost_terrain;

    while (file >> str) {
        file >> n;
        file >> groupid;
        fwrite(&n, sizeof(int), 1, output);
        fwrite(&groupid, sizeof(int), 1, output);
        printf("%s %d %d\n", str.c_str(), n, groupid);
        
        for (int i = 0; i < n; i++) {
            file >> tile.x >> tile.y >> tile.width >> tile.height >> tile.objid >> tile.zindex;
            printf("%.2f %.2f %.2f %.2f %d %d", tile.x, tile.y, tile.width, tile.height, tile.objid, tile.zindex);            
            fwrite(&tile, sizeof(Tile), 1, output);
            if (groupid == 1) {
                file >> coast_n >> cost_terrain;
                fwrite(&coast_n, sizeof(int), 1, output);
                fwrite(&cost_terrain, sizeof(int), 1, output);
                printf(" %d %d", coast_n, cost_terrain);                
            }
            printf("\n");            
        }
    }

    fclose(output);
    file.close();
}


int main() {    
    txt_to_bin("world.txt", "../src/resources/data/maps/world.bin");
    return 0;
}