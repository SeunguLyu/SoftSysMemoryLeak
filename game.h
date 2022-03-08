#include <time.h>
#include <ncurses.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define WIDTH 100
#define HEIGHT 40
#define DELAY 10000
#define MAX_ENEMY 1000

struct Enemy
{
    int live;
    int x;
    int y;
    int current_move_frame;
};

void title(WINDOW *win);
void gameover(WINDOW *win);
void resize();
void gameplay(WINDOW *win);
void initialize_colors();
void spawn_enemy();

void draw_player(WINDOW *win);
void draw_enemies(WINDOW *win);
void player_enemy_collision_check();
void draw_rectangle(WINDOW *win, int y1, int x1, int y2, int x2);
void draw_score_UI(WINDOW *win);