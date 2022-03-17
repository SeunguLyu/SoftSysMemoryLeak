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
#define MAX_BULLET 100

#define TIME_SCORE 1
#define KILL_SCORE 10
#define DIFFICULTY_SCORE_LEVEL 50
#define MAX_DIFFICULTY_LEVEL 50

#define MAX_PLAYER_MOVE_FRAME 20
#define MIN_PLAYER_MOVE_FRAME 8

#define MAX_ENEMY_MOVE_FRAME 50
#define MIN_ENEMY_MOVE_FRAME 15

#define MAX_ENEMY_SPAWN_FRAME 200
#define MIN_ENEMY_SPAWN_FRAME 5

#define MAX_BULLET_MOVE_FRAME 10
#define MIN_BULLET_MOVE_FRAME 2

#define MAX_BULLET_SPAWN_FRAME 100
#define MIN_BULLET_SPAWN_FRAME 20

#define MAX_SCORE_UP_FRAME 100
#define MIN_SCORE_UP_FRAME 10

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

typedef struct PowerUp
{
    int live;
    int x;
    int y;
}PowerUp;

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

void draw_pow_up(WINDOW *win);
void spawn_power_up(int type);
void player_power_up_collision_check(WINDOW *win);

void difficulty_control();