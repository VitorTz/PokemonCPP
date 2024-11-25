from pathlib import Path
from pytmx import TiledObjectGroup, TiledObject
from pytmx.util_pygame import load_pygame
import shutil
import pygame

MAPS_PATH = Path("../src/resources/data/maps/")

def main() -> None:
    d = pygame.display.set_mode((50, 50))

    for file in MAPS_PATH.iterdir():
        if file.suffix == ".tmx":
            tiled = load_pygame(file)
            output = open(MAPS_PATH / f"{file.stem}.txt", "w")
            tiledgroups: list[TiledObjectGroup] = [x for x in tiled.layers]
            for tiledgroup in tiledgroups:
                if not isinstance(tiledgroup, TiledObjectGroup):
                    continue
                objs: list[TiledObject] = [x for x in tiledgroup]                
                output.write(f"{tiledgroup.properties['group-id']} {len(objs)}\n")
                for obj in objs:
                    output.write(f"{obj.x} {obj.y} {obj.width} {obj.height} {obj.properties.get('obj-id', -1)} {obj.properties.get('zindex', 0)} {obj.properties.get('terrain', 0)} {obj.properties.get('n', 0)} {obj.properties.get('direction', 'd')} ")
                    if (obj.properties.get("source") and tiledgroup.name != "Coast"):
                        imagepath = "./resources/graphics" + obj.properties["source"].split("graphics")[1]
                    else:
                        imagepath = './'                                        
                    output.write(f"{imagepath}\n")            
            output.close()
            shutil.copy(MAPS_PATH / f"{file.stem}.txt", f"{file.stem}.txt")
        
if __name__ == "__main__":
    main()