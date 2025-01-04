import pygame
from pytmx import load_pygame, TiledMap, TiledObjectGroup, TiledObject, TiledTileLayer


COAST_ID = 1


def main() -> None:
    map_name = "world"
    
    disp = pygame.display.set_mode((400, 400))
    tiled_map: TiledMap = load_pygame(f"../src/resources/data/maps/{map_name}.tmx")

    output = open(f"{map_name}.txt", "w+")
    output.write(f"{tiled_map.width * tiled_map.tilewidth} {tiled_map.height * tiled_map.tilewidth}\n./resources/data/maps/{map_name}.png\n")

    for l in tiled_map.layers:
        if (isinstance(l, TiledTileLayer)):
            continue
        layer: TiledObjectGroup = l
        objs: list[TiledObject] = [x for x in layer]
        output.write(f"{layer.name} {len(objs)} {layer.properties["group-id"]}\n")
        for obj in objs:
            try:
                output.write(f"{obj.x} {obj.y} {obj.width} {obj.height} {obj.properties['obj-id']} {obj.properties['zindex']}")
                if (layer.properties['group-id'] == COAST_ID):
                    output.write(f" {obj.properties['n']} {obj.properties['terrain']}")
                output.write('\n')
            except Exception as e:
                print(layer.properties["group-id"], e)
        
        
if __name__ == "__main__":
    main()