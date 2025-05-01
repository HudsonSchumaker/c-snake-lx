# Snake Game in C

This is a simple implementation of the classic Snake game written in C using the `ncurses` library.

## Features

- Playable Snake game with a growing snake and randomly placed fruits.
- Collision detection with walls and the snake's own body.
- Simple ASCII graphics rendered using `ncurses`.

## How to Build and Run

### Prerequisites

- GCC compiler
- `ncurses` library installed on your system

### Build

To compile the game, run the following command:

```sh
make build
```

This will generate an executable named `snake`.

### Run

To play the game, execute the following command:

```sh
./snake
```

### Controls

- Use the arrow keys to move the snake.
- Press `q` to quit the game.

### Game Rules

- The snake moves continuously in the current direction.
- Collect the `*` (fruit) to grow the snake.
- The game ends if the snake collides with the walls or itself.

### File Structure

- `main.c`: Contains the game logic and rendering code.
- `Makefile`: Build script for compiling the game.
- `snake`: The compiled executable (generated after running `make build`).

### License

This project is open-source and available under the MIT License.
