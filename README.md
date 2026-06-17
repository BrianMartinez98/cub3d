# cub3D

Primera base de `cub3D` creada desde el proyecto `so_long`.

En este punto el proyecto ya tiene el primer raycasting basico. El objetivo de
esta fase es confirmar que la infraestructura funciona:

- MiniLibX compila y abre ventana.
- El ejecutable se llama `cub3D`.
- El programa acepta archivos `.cub`.
- El parser lee texturas `NO`, `SO`, `WE`, `EA`.
- El parser lee colores `F` y `C`.
- El mapa valida caracteres, cierre por muros y un unico jugador.
- Se dibuja una primera vista 3D con raycasting basico y paredes planas.

## Build

```bash
make
```

## Run

```bash
./cub3D maps/basic.cub
```

## Guia de estudio

Lee las guias de los pasos aqui:

```text
docs/paso_1_raycasting_basico.md
docs/paso_2_movimiento_colisiones.md
```

## Controls

| Key | Action |
|---|---|
| `W` / Up arrow | Avanzar |
| `S` / Down arrow | Retroceder |
| `A` | Strafe izquierda |
| `D` | Strafe derecha |
| Left arrow | Girar izquierda |
| Right arrow | Girar derecha |
| `ESC` | Cerrar |

## Siguiente paso

Anadir texturas a las paredes usando las rutas `NO`, `SO`, `WE` y `EA`.
