# Paso 2: movimiento, rotacion y colisiones

## Objetivo

En el paso anterior el motor ya dibujaba una escena 3D, pero la camara estaba
quieta. En este paso hacemos que el jugador pueda moverse por el mapa.

Controles actuales:

- `W` o flecha arriba: avanzar
- `S` o flecha abajo: retroceder
- `A`: strafe izquierda
- `D`: strafe derecha
- flecha izquierda: girar izquierda
- flecha derecha: girar derecha
- `ESC`: cerrar

## Donde vive el cambio

El archivo principal de este paso es:

```text
ft_move.c
```

El flujo es:

1. MiniLibX detecta una tecla.
2. Llama a `key_hook()`.
3. `key_hook()` decide si hay movimiento o rotacion.
4. Si algo cambia, llama a `render_frame()`.

## Movimiento hacia delante y atras

El jugador tiene un vector direccion:

```text
dir_x
dir_y
```

Si mira al norte, por ejemplo:

```text
dir_x = 0
dir_y = -1
```

Avanzar significa sumar esa direccion a la posicion:

```text
pos_x += dir_x * MOVE_SPEED
pos_y += dir_y * MOVE_SPEED
```

Retroceder es lo mismo, pero en negativo.

## Strafe

Strafe significa moverse de lado sin girar la camara.

Si la direccion es `(dir_x, dir_y)`, un vector perpendicular es:

```text
(dir_y, -dir_x)
```

Ese vector se usa para moverse hacia la izquierda. El contrario se usa para
moverse hacia la derecha.

## Colisiones

La funcion `is_wall()` comprueba si una posicion futura cae en:

- una pared `1`
- un espacio `' '`
- fuera del mapa

Si cae ahi, no deja moverse.

La funcion `try_move()` comprueba X e Y por separado:

```text
primero intenta mover X
luego intenta mover Y
```

Eso permite deslizarse por paredes. Si intentas moverte en diagonal contra una
pared, el eje bloqueado se cancela, pero el otro puede seguir avanzando.

## Rotacion

Para girar no cambiamos la posicion. Cambiamos:

```text
dir_x / dir_y
plane_x / plane_y
```

`dir` dice hacia donde miras.

`plane` representa el plano de camara, que controla el campo de vision.

Ambos tienen que girar juntos. Si solo giras `dir`, la camara se rompe. Si solo
giras `plane`, tambien.

La rotacion usa esta matriz 2D:

```text
new_x = old_x * cos(a) - old_y * sin(a)
new_y = old_x * sin(a) + old_y * cos(a)
```

Donde `a` es el angulo de giro.

## Por que se rerenderiza despues de cada tecla

El raycasting depende de:

```text
pos_x, pos_y, dir_x, dir_y, plane_x, plane_y
```

Si cualquiera cambia, la imagen vieja ya no sirve. Por eso `key_hook()` llama a:

```text
render_frame(data);
```

## Siguiente paso recomendado

Ahora que el motor se puede recorrer, el siguiente paso natural es cargar
texturas reales en las paredes.

Para eso habra que:

- cargar cuatro XPM: norte, sur, oeste y este
- detectar que lado de pared golpea cada rayo
- calcular la coordenada X dentro de la textura
- pintar cada pixel de pared con el color de la textura
