#include <iostream>
#include <fstream>
#include <cassert>
#include <string>


#define COAST_GROUP 1
#define SPRITES_GROUP 3


typedef struct _tile {
    float x;
    float y;
    float width;
    float height;
    int objid;
    int zindex;
} Tile;


void read_tiledmap(const char* input_path) {
    std::ifstream file(input_path);

    assert(file.is_open());    
    
    int map_width, map_height;
    int n;
    int groupid;
    int coast_n;
    int cost_terrain;
    Tile tile;
    std::string str;
    
    file >> map_width;
    file >> map_height;
    file >> str;

    std::cout << map_width << ' ' << map_height << '\n' << str << '\n';    

    while (file >> str) {
        file >> n;
        file >> groupid;
        std::cout << str << ' ' << n << ' ' << groupid << '\n';
        
        for (int i = 0; i < n; i++) {
            file >> tile.x >> tile.y >> tile.width >> tile.height >> tile.objid >> tile.zindex;
            std::cout << tile.x << ' ' << tile.y << ' ' << tile.width << ' ' << tile.height << ' ' << tile.objid << ' ' << tile.zindex;
            
            if (groupid == 1) {
                file >> coast_n >> cost_terrain;
                std::cout << ' ' << coast_n << ' ' << cost_terrain;                
            } else if (groupid == 3) {
                file >> str;
                std::cout << ' ' << str;                
            }
            std::cout << '\n';
        }
    }
    
    file.close();
}


int main() {                
    read_tiledmap("world.txt");
    return 0;
}