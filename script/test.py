from pathlib import Path
from PIL import Image
import sys


def main() -> None:
    file = Path(sys.argv[1])
    rows = int(sys.argv[2])
    cols = int(sys.argv[3])

    img = Image.open(file)
    left = 0
    top = 0    
    
    width = img.width / cols
    height = img.height / rows
    n = 0

    for i in range(rows):
        for j in range(cols):
            new_image = img.crop((left, top, left + width, top + height))
            new_image.save(f"sand-1-{n}.png", "png")
            n += 1
            left += width
        top += height
        left = 0

    if (file.exists() is False):
        print("erro")
    

if __name__ == "__main__":
    main()