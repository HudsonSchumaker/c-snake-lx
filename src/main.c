#include <time.h>
#include <stdlib.h>
#include <ncurses.h>
#include <stdbool.h>

#define WIDTH  60
#define T_WIDTH 23
#define HEIGHT 15
#define MAX_LENGTH 100

typedef struct {
    int x, y;
} point_t;

point_t snake[MAX_LENGTH];
int snake_length = 1;

point_t fruit;
int direction = KEY_RIGHT; // Initial direction

void init_game() {
    snake[0].x = WIDTH  / 2;
    snake[0].y = HEIGHT / 2;
    snake_length = 1;

    // Place the first fruit
    srand(time(0));
    fruit.x = rand() % WIDTH;
    fruit.y = rand() % HEIGHT;
}

void draw_board() {
    clear();

    // Draw the border
    for (int i = 0; i < T_WIDTH + 2; i++) mvprintw(0, i, "#");
    mvprintw(0, T_WIDTH + 1 , "Schumaker Team");
    for (int i = 38; i < WIDTH + 2; i++) mvprintw(0, i, "#");
    
    for (int i = 0; i < WIDTH + 2; i++) mvprintw(HEIGHT + 1, i, "#");
    for (int i = 1; i <= HEIGHT; i++) {
        mvprintw(i, 0, "#");
        mvprintw(i, WIDTH + 1, "#");
    }

    // Draw the fruit
    mvprintw(fruit.y + 1, fruit.x + 1, "*");

    // Draw the snake
    for (int i = 0; i < snake_length; i++) {
        if (i == 0) {
            mvprintw(snake[i].y + 1, snake[i].x + 1, "@");
        }
        else {
            mvprintw(snake[i].y + 1, snake[i].x + 1, "O");
        }
    }
}

void update_snake() {
    // Move the snake's body
    for (int i = snake_length - 1; i > 0; i--) {
        snake[i] = snake[i - 1];
    }

    // Move the snake's head
    switch (direction) {
        case KEY_UP:    snake[0].y--; break;
        case KEY_DOWN:  snake[0].y++; break;
        case KEY_LEFT:  snake[0].x--; break;
        case KEY_RIGHT: snake[0].x++; break;
    }

    // Check for collision with fruit
    if (snake[0].x == fruit.x && snake[0].y == fruit.y) {
        snake_length++;
        if (snake_length > MAX_LENGTH) snake_length = MAX_LENGTH;

        // Place a new fruit
        fruit.x = rand() % WIDTH;
        fruit.y = rand() % HEIGHT;
    }
}

bool check_collision() {
    // Check collision with walls
    if (snake[0].x < 0 || snake[0].x >= WIDTH || snake[0].y < 0 || snake[0].y >= HEIGHT) {
        return true;
    }

    // Check collision with itself
    for (int i = 1; i < snake_length; i++) {
        if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
            return true;
        }
    }

    return false;
}

int main() {
    initscr();
    curs_set(0);
    keypad(stdscr, TRUE);
    noecho();
    timeout(148); // Set a timeout for getch()

    init_game();

    for(;;){
        draw_board();
        int ch = getch();
        if (ch == 'q') break;

        // Update direction (prevent reverse direction)
        if ((ch == KEY_UP    && direction != KEY_DOWN)  ||
            (ch == KEY_DOWN  && direction != KEY_UP)    ||
            (ch == KEY_LEFT  && direction != KEY_RIGHT) ||
            (ch == KEY_RIGHT && direction != KEY_LEFT)) {
            direction = ch;
        }

        update_snake();

        if (check_collision()) {
            mvprintw(HEIGHT / 2, WIDTH / 2 - 5, "GAME OVER!");
            refresh();
            getch();
            break;
        }

        refresh();
    }

    int i;
    scanf("%d", &i); 
    endwin();
    return 0;
}

