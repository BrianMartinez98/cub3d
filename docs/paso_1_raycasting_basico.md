# Paso 1: de mapa 2D a raycasting basico

## Idea general

`so_long` dibuja un mapa desde arriba: cada caracter del mapa se convierte en
un tile de 32x32 pixeles.

`cub3D` hace otra cosa: el jugador tiene una posicion y una direccion. Para
cada columna de la pantalla lanzamos un rayo. Ese rayo avanza por el mapa hasta
chocar contra una pared. Cuanto mas cerca este la pared, mas alta se dibuja la
columna.

Este primer paso no usa texturas. Solo pinta:

- techo con el color `C` del `.cub`
- suelo con el color `F` del `.cub`
- paredes grises calculadas por raycasting

## Por que no active el flood fill obligatorio

En `so_long`, flood fill sirve para comprobar si el jugador puede llegar a los
coleccionables y a la salida.

En `cub3D`, el obligatorio no pide eso. Lo importante es que el mapa este
cerrado. Si hay un hueco al vacio, el raycaster podria mirar fuera del array.

Por eso hay dos piezas separadas:

- `checker.c`: validacion obligatoria de `cub3D`
- `flood_fill.c`: herramienta futura para hacer un videojuego con objetivos

## Archivos importantes

### `cub3d.h`

Define el estado principal `t_data`.

Campos nuevos importantes:

- `pos_x`, `pos_y`: posicion real del jugador en el mapa, con decimales
- `dir_x`, `dir_y`: hacia donde mira el jugador
- `plane_x`, `plane_y`: plano de camara, controla el campo de vision
- `frame`: imagen en memoria donde se pinta cada pixel antes de mostrarla

### `ft_init.c`

Lee el archivo `.cub`.

Proceso:

1. Comprueba extension `.cub`.
2. Lee todas las lineas.
3. Extrae texturas `NO`, `SO`, `WE`, `EA`.
4. Extrae colores `F` y `C`.
5. Copia el mapa.
6. Valida mapa.
7. Inicializa la camara segun `N`, `S`, `E` o `W`.

La funcion `set_camera()` traduce la letra del jugador en vectores.

Ejemplo:

```text
N significa:
dir_x = 0
dir_y = -1
```

Eso quiere decir: no mira a izquierda/derecha, mira hacia arriba en el mapa.

### `checker.c`

Valida el mapa.

Reglas actuales:

- Solo acepta `0`, `1`, espacios y `N/S/E/W`.
- Debe haber exactamente un jugador.
- Cada casilla caminable debe estar rodeada por mapa valido, no por vacio.

### `raycast.c`

Es el primer corazon de `cub3D`.

Para cada columna `x` de la pantalla:

1. Convierte `x` en una posicion dentro de la camara.
2. Calcula la direccion del rayo.
3. Averigua en que celda del mapa empieza.
4. Usa DDA para avanzar celda por celda.
5. Para al encontrar una pared.
6. Calcula la distancia perpendicular.
7. Dibuja una columna:
   - techo arriba
   - pared en medio
   - suelo abajo

## Que es DDA

DDA significa que no avanzamos el rayo pixel a pixel. Eso seria lento y confuso.

Avanzamos de linea de grid a linea de grid:

- si el siguiente borde vertical esta mas cerca, entramos en la celda de al lado
- si el siguiente borde horizontal esta mas cerca, entramos en la celda de arriba/abajo

Cuando la celda contiene `1`, el rayo ha chocado con una pared.

## Por que se usa distancia perpendicular

Si usamos la distancia cruda del rayo, las paredes laterales se deforman como si
la imagen fuera curva.

Para evitarlo usamos la distancia perpendicular a la camara. Eso mantiene las
paredes rectas.

## Como probar

```bash
cd /mnt/c/Users/brian/Documents/Codex/2026-06-04/files-mentioned-by-the-user-so/outputs/cub3D
make
./cub3D maps/basic.cub
```

Deberias ver una ventana 1024x768 con techo, suelo y paredes planas.

## Siguiente paso recomendado

El siguiente bloque deberia ser movimiento:

- `W/S`: avanzar y retroceder
- `A/D`: strafe izquierda/derecha
- flechas izquierda/derecha: rotar camara
- colision contra paredes

Ese paso ya usara `pos_x`, `pos_y`, `dir_x`, `dir_y`, `plane_x` y `plane_y`.
