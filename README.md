# Conway's Game of Life in C

A small Conway's Game of Life application written in C with SDL2.

## Features

- Draw live cells with the left mouse button
- Pause and resume with Space
- Clear the board with R
- Change the simulation speed with the arrow keys
- Draw the board on a visible grid

## Requirements

- A C compiler
- SDL2
- `pkg-config`
- `make`

On Debian or Ubuntu, install the dependencies with:

```sh
sudo apt install build-essential libsdl2-dev pkg-config
```

## Build and run

```sh
make
make run
```

Remove the local executable with:

```sh
make clean
```

## Controls

| Key or action | Result |
| --- | --- |
| Left mouse button | Add live cells |
| Space | Pause or resume |
| R | Clear the board |
| Up arrow | Increase the speed |
| Down arrow | Decrease the speed |

## Project status

The simulation currently uses a fixed 100 by 100 cell grid. The next improvements are automated tests, better timing, and clearer separation between the simulation and SDL rendering.
