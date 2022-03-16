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
#define MAX_ENEMY 500
#define MAX_BULLET 30

typedef struct Enemy
{
    int live;
    int x;
    int y;
    int current_move_frame;
}Enemy;

typedef struct Bullet
{
    int live;
    int x;
    int y;
    int dir;
    int current_move_frame;
    int travel_distance;
}Bullet;

void title(WINDOW *win);
void gameover(WINDOW *win);
void resize();
void gameplay(WINDOW *win);
void initialize_colors();
void spawn_enemy();
void enemy_move();

void draw_player(WINDOW *win);
void draw_enemies(WINDOW *win);
void player_enemy_collision_check();
void draw_rectangle(WINDOW *win, int y1, int x1, int y2, int x2);
void draw_score_UI(WINDOW *win);

void draw_bullets(WINDOW *win);
void bullet_enemy_collision_check();
void bullet_move();
void spawn_bullet();