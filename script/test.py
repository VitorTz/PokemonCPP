

def map_x_to_y(x):
    # Limites de x e y
    x_min, x_max = 64, 8096
    y_min, y_max = 0.5, 5

    # Coeficientes da transformação linear
    a = (y_max - y_min) / (x_min - x_max)
    b = y_max - a * x_min

    # Transformação de x para y
    y = a * x + b
    return y


for i in range(64, 8097):
    print(map_x_to_y(i))