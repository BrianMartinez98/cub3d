# so_long

A small 2D tile-based game implemented in C as part of the 42 curriculum.

The project uses MiniLibX to render a map loaded from a `.ber` file. The player moves through the map, collects all collectibles, and exits once the level is complete.

## Features

- Map parsing from `.ber` files
- Wall, player, collectible, exit, and background tiles
- Basic path validation using flood fill
- Keyboard movement with `WASD` or arrow keys
- Move counter printed in the terminal
- Minimal XPM assets included

## Controls

| Key | Action |
|---|---|
| `W` / Up arrow | Move up |
| `A` / Left arrow | Move left |
| `S` / Down arrow | Move down |
| `D` / Right arrow | Move right |
| `ESC` | Close the game |

## Build

This project targets Linux and depends on MiniLibX/X11.

On Debian/Ubuntu-like systems, install the X11 dependencies first:

```bash
sudo apt-get install gcc make xorg libxext-dev libbsd-dev
```

Then build the project:

```bash
make
```

## Run

```bash
./so_long maps/a.ber
```

Other sample maps are available in the `maps/` directory.

## Project structure

```text
.
├── get_next_line/      # line reader used for map parsing
├── ft_printf/          # small printf implementation used for terminal output
├── maps/               # sample .ber maps
├── minilibx-linux/     # MiniLibX dependency
├── rs/                 # XPM tile assets
├── *.c                 # game source files
├── so_long.h           # main project header
└── Makefile
```

## Note

This repository is a cleaned public version of my 42 `so_long` project. The implementation is intentionally kept close to the original project to preserve progression across the curriculum.
