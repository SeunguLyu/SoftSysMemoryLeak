#include "game.h"

int g_terminal_y = 0, g_terminal_x = 0;

int g_game_status = 0;
int g_title_selection = 0;

int g_player_dir = -1;
int g_player_x = WIDTH/2;
int g_player_y = (HEIGHT-6)/2 + 6;

int g_player_move_frame = 20;
int g_current_player_move_frame = 0;
int g_player_attack_frame = 30;
int g_current_player_attack_frame = 0;

int g_current_pow = 8;
int g_current_spd = 1;
int g_current_score = 0;

int g_enemy_move_frame = 50;
int g_enemy_spawn_frame = 300;
int g_current_enemy_spawn_frame = 0;
Enemy g_enemies[MAX_ENEMY];
int g_enemy_position_map[WIDTH][HEIGHT];

int g_bullet_move_frame = 5;
int g_bullet_spawn_frame = 100;
int g_current_bullet_spawn_frame = 0;
int g_bullet_dir = 0;
Bullet g_bullet[MAX_BULLET];

const char TITLE_LOGO[][300] = {

    "███╗░░░███╗███████╗███╗░░░███╗░█████╗░██████╗░██╗░░░██╗██╗░░░░░███████╗░█████╗░██╗░░██╗",
    "████╗░████║██╔════╝████╗░████║██╔══██╗██╔══██╗╚██╗░██╔╝██║░░░░░██╔════╝██╔══██╗██║░██╔╝",
    "██╔████╔██║█████╗░░██╔████╔██║██║░░██║██████╔╝░╚████╔╝░██║░░░░░█████╗░░███████║█████═╝░",
    "██║╚██╔╝██║██╔══╝░░██║╚██╔╝██║██║░░██║██╔══██╗░░╚██╔╝░░██║░░░░░██╔══╝░░██╔══██║██╔═██╗░",
    "██║░╚═╝░██║███████╗██║░╚═╝░██║╚█████╔╝██║░░██║░░░██║░░░███████╗███████╗██║░░██║██║░╚██╗",
    "╚═╝░░░░░╚═╝╚══════╝╚═╝░░░░░╚═╝░╚════╝░╚═╝░░╚═╝░░░╚═╝░░░╚══════╝╚══════╝╚═╝░░╚═╝╚═╝░░╚═╝",
};

const char GAME_OVER_LOGO[][300] = {
    
    "░██████╗░░█████╗░███╗░░░███╗███████╗░█████╗░██╗░░░██╗███████╗██████╗░",
    "██╔════╝░██╔══██╗████╗░████║██╔════╝██╔══██╗██║░░░██║██╔════╝██╔══██╗",
    "██║░░██╗░███████║██╔████╔██║█████╗░░██║░░██║╚██╗░██╔╝█████╗░░██████╔╝",
    "██║░░╚██╗██╔══██║██║╚██╔╝██║██╔══╝░░██║░░██║░╚████╔╝░██╔══╝░░██╔══██╗",
    "╚██████╔╝██║░░██║██║░╚═╝░██║███████╗╚█████╔╝░░╚██╔╝░░███████╗██║░░██║",
    "░╚═════╝░╚═╝░░╚═╝╚═╝░░░░░╚═╝╚══════╝░╚════╝░░░░╚═╝░░░╚══════╝╚═╝░░╚═╝",
};

const char TITLE_DESCRIPTION[][100] = {
    "A long time ago in a SoftSys class far, far away...",
    "An Oliner decided to finish their project in a single day...",
    "It worked perfectly on the day it was presented...",
    "Without knowing that the memory was leaking!!!",
    "You accidentally compiled the program...",
    "And now you have to free all the leaking memories!"
};

const char EXTRA_DESCRIPTION[][30] = {
    "Start Game",
    "Exit Game",
    "Press W,A,S,D to move",
    "Press Enter to Select",
    "Your Final Score: ",
    "Press Any Key to Exit Game...",
};

void title(WINDOW *win)
{
    //wclear(win);
    werase(win);
    box(win,0,0);

    char in = getch();
    int end = 0;

    switch(in)
    {
        case 'w':
            g_title_selection -= 1;
            break;
        case 's':
            g_title_selection += 1;
            break;
        case '\n':
            end = 1;
            break;
    }

    if (g_title_selection == 2)
    {
        g_title_selection = 0;
    }
    else if (g_title_selection == -1)
    {
        g_title_selection = 1;
    }
    
    flushinp();

    wattron(win,COLOR_PAIR(3));
    for (int i = 0; i<6; i++)
    {
        mvwprintw(win, 5+i, 7, TITLE_LOGO[i]);
    }
    wattroff(win,COLOR_PAIR(3));

    for (int i = 0; i<6; i++)
    {
        int xpos = (WIDTH - strlen(TITLE_DESCRIPTION[i]))/2;
        mvwprintw(win, 14+2*i, xpos, TITLE_DESCRIPTION[i]);
    }

    int xpos = (WIDTH - strlen(EXTRA_DESCRIPTION[2]))/2;
    wattron(win,COLOR_PAIR(1));
    mvwprintw(win, 27, xpos, EXTRA_DESCRIPTION[2]);
    xpos = (WIDTH - strlen(EXTRA_DESCRIPTION[3]))/2;
    mvwprintw(win, 29, xpos, EXTRA_DESCRIPTION[3]);
    wattroff(win,COLOR_PAIR(1));
    
    if (g_title_selection == 0)
    {
        int xpos = (WIDTH - strlen(EXTRA_DESCRIPTION[0]))/2;
        wattron(win,COLOR_PAIR(2));
        mvwprintw(win, 32, xpos, EXTRA_DESCRIPTION[0]);
        wattroff(win,COLOR_PAIR(2));
        wattron(win,COLOR_PAIR(4));
        xpos = (WIDTH - strlen(EXTRA_DESCRIPTION[1]))/2;
        mvwprintw(win, 34, xpos, EXTRA_DESCRIPTION[1]);
        wattroff(win,COLOR_PAIR(4));
    }
    else
    {
        int xpos = (WIDTH - strlen(EXTRA_DESCRIPTION[0]))/2;
        wattron(win,COLOR_PAIR(4));
        mvwprintw(win, 32, xpos, EXTRA_DESCRIPTION[0]);
        wattroff(win,COLOR_PAIR(4));
        xpos = (WIDTH - strlen(EXTRA_DESCRIPTION[1]))/2;
        wattron(win,COLOR_PAIR(2));
        mvwprintw(win, 34, xpos, EXTRA_DESCRIPTION[1]);
        wattroff(win,COLOR_PAIR(2));
    }

    if (end == 1)
    {
        if (g_title_selection == 0)
        {
            g_game_status = 2;
            wclear(win);
        }
        else
        {
            g_game_status = -1;
        }
    }
    
    wrefresh(win);
    usleep(DELAY);
}

void gameover(WINDOW *win)
{
    wclear(win);
    //werase(win);
    box(win,0,0);

    wattron(win,COLOR_PAIR(3));
    for (int i = 0; i<6; i++)
    {
        mvwprintw(win, 15+i, 15, GAME_OVER_LOGO[i]);
    }
    wattroff(win,COLOR_PAIR(3));

    int xpos = (WIDTH - strlen(EXTRA_DESCRIPTION[4]))/2;
    wattron(win,COLOR_PAIR(5));
    mvwprintw(win, 25, xpos, EXTRA_DESCRIPTION[4]);
    wattroff(win,COLOR_PAIR(5));

    wattron(win,COLOR_PAIR(1));
    xpos = (WIDTH - strlen(EXTRA_DESCRIPTION[5]))/2;
    mvwprintw(win, 30, xpos, EXTRA_DESCRIPTION[5]);
    wattroff(win,COLOR_PAIR(1));

    g_game_status = -1;

    nodelay(stdscr, 0);
    
    wrefresh(win);
    usleep(DELAY);
}

void resize()
{
    clear();
    mvprintw(1, 1, "Please resize the terminal and re-run the program");
    mvprintw(2, 1, "The size should be at least 100 columns and 40 lines");
    refresh();
}

void draw_player(WINDOW *win)
{
    wattron(win,COLOR_PAIR(1));
    mvwprintw(win, g_player_y, g_player_x,"⚇");
    wattroff(win,COLOR_PAIR(1));
}

void draw_enemies(WINDOW *win)
{
    wattron(win,COLOR_PAIR(5));
    for (int i = 0; i < MAX_ENEMY; i++)
    {
        if (g_enemies[i].live == 1)
        {
            mvwprintw(win, g_enemies[i].y, g_enemies[i].x,"⚉");
        }
    }
    wattroff(win,COLOR_PAIR(5));
}

void draw_bullets(WINDOW *win)
{
    wattron(win,COLOR_PAIR(4));
    for (int i = 0; i < MAX_BULLET; i++)
    {
        if (g_bullet[i].live == 1)
        {
            mvwprintw(win, g_bullet[i].y, g_bullet[i].x,"•");
        }
    }
    wattroff(win,COLOR_PAIR(4));
}

void player_enemy_collision_check()
{
    for (int i = 0; i < MAX_ENEMY; i++)
    {
        if (g_enemies[i].x == g_player_x && g_enemies[i].y == g_player_y && g_enemies[i].live == 1)
        {
            g_game_status = 3;
        }
    }
}

void bullet_enemy_collision_check()
{
    for (int i = 0; i < MAX_ENEMY; i++)
    {
        if (g_enemies[i].live == 0)
        {
            continue;
        }
        for (int j = 0; j < MAX_BULLET; j++)
        {
            if (g_bullet[j].live == 0)
            {
                continue;
            }
            if (g_bullet[j].x == g_enemies[i].x && g_bullet[j].y == g_enemies[i].y)
            {
                g_enemies[i].live = 0;
                g_bullet[j].live = 0;
                g_current_score += 10;
                break;
            }
        }
    }
}

void enemy_move()
{
    for (int i = 0; i<MAX_ENEMY; i++)
    {
        if (g_enemies[i].live == 1)
        {
            if (g_enemies[i].current_move_frame >= g_enemy_move_frame)
            {
                int x_axis, y_axis;
                int x,y;

                x_axis = g_player_x - g_enemies[i].x;
                y_axis = g_player_y - g_enemies[i].y;

                x_axis = x_axis/abs(x_axis);
                y_axis = y_axis/abs(y_axis);

                if (x_axis != 0 && y_axis != 0)
                {
                    switch(rand() % 2)
                    {
                        case 0:
                            x = g_enemies[i].x + x_axis;
                            y = g_enemies[i].y;
                            break;
                        case 1:
                            x = g_enemies[i].x;
                            y = g_enemies[i].y + y_axis;
                            break;
                    }
                }
                else if (x_axis != 0)
                {
                    x = g_enemies[i].x + x_axis;
                    y = g_enemies[i].y;
                }
                else if (y_axis != 0)
                {
                    x = g_enemies[i].x;
                    y = g_enemies[i].y + y_axis;
                }

                if (x == 1 || x == (WIDTH - 1) || y == 6 || y == (HEIGHT - 1))
                {
                    continue;
                }

                if (g_enemy_position_map[x][y] == 0)
                {
                    g_enemy_position_map[g_enemies[i].x][g_enemies[i].y] = 0;
                    g_enemies[i].x = x;
                    g_enemies[i].y = y;
                    g_enemy_position_map[x][y] = 1;

                    g_enemies[i].current_move_frame = 0;
                }
            }
            else
            {
                g_enemies[i].current_move_frame += 1;
            }
        }
    }
}

void bullet_move()
{
    for (int i = 0; i<MAX_BULLET; i++)
    {
        if (g_bullet[i].live == 1)
        {
            if (g_bullet[i].current_move_frame >= g_bullet_move_frame)
            {
                int x,y;
                x = g_bullet[i].x;
                y = g_bullet[i].y;
                switch(g_bullet[i].dir)
                {
                    case 0:
                        y -= 1;
                        break;
                    case 1:
                        x += 1;
                        y -= 1;
                        break;
                    case 2:
                        x += 1;
                        break;
                    case 3:
                        x += 1;
                        y += 1;
                        break;
                    case 4:
                        y += 1;
                        break;
                    case 5:
                        x -= 1;
                        y += 1;
                        break;
                    case 6:
                        x -= 1;
                        break;
                    case 7:
                        x -= 1;
                        y -= 1;
                        break;
                }

                if (x == 1 || x == (WIDTH - 1) || y == 6 || y == (HEIGHT - 1))
                {
                    g_bullet[i].live = 0;
                }
                else
                {
                    g_bullet[i].x = x;
                    g_bullet[i].y = y;
                    g_bullet[i].travel_distance += 1;
                    g_bullet[i].current_move_frame = 0;
                }

                if (g_bullet[i].travel_distance == g_current_pow * 2 + 4)
                {
                    g_bullet[i].live = 0;
                }
                
            }
            else
            {
                g_bullet[i].current_move_frame += 1;
            }
        }
    }
}

void spawn_enemy()
{
    if (g_current_enemy_spawn_frame >= g_enemy_spawn_frame)
    {
        int empty;
        for (int i = 0; i<MAX_ENEMY; i++)
        {
            if (g_enemies[i].live == 0)
            {
                empty = i;
                break;
            }
            else if (i == MAX_ENEMY - 1)
            {
                return;
            }
        }

        int x,y;
        int pattern;

        pattern = rand() % 4;

        switch(pattern)
        {
            case 0:
                x = 2;
                y = 7+(rand() % (HEIGHT-8));
                break;
            case 1:
                x = 2+(rand() % (WIDTH-4));
                y = 7;
                break;
            case 2:
                x = WIDTH - 3;
                y = 7+(rand() % (HEIGHT-8));
                break;
            case 3:
                x = 2+(rand() % (WIDTH-4));
                y = HEIGHT - 3;
                break;
        }

        if (g_enemy_position_map[x][y] == 0)
        {
            g_enemies[empty].live = 1;
            g_enemies[empty].x = x;
            g_enemies[empty].y = y;
            g_enemies[empty].current_move_frame = 0;

            g_enemy_position_map[x][y] = 1;

            g_current_enemy_spawn_frame = 0;
        }
    }
    else
    {
        g_current_enemy_spawn_frame += 1;
    }
}

void spawn_bullet()
{
    if (g_current_bullet_spawn_frame >= g_bullet_spawn_frame)
    {
        int current_dir = g_bullet_dir;

        for (int j = 0; j <g_current_pow; j++)
        {
            int empty;
            for (int i = 0; i<MAX_BULLET; i++)
            {
                if (g_bullet[i].live == 0)
                {
                    empty = i;
                    break;
                }
                else if (i == MAX_BULLET - 1)
                {
                    g_current_bullet_spawn_frame = 0;
                    return;
                }
            }

            int x, y;

            x = g_player_x;
            y = g_player_y;

            switch(current_dir)
            {
                case 0:
                    y -= 1;
                    break;
                case 1:
                    x += 1;
                    y -= 1;
                    break;
                case 2:
                    x += 1;
                    break;
                case 3:
                    x += 1;
                    y += 1;
                    break;
                case 4:
                    y += 1;
                    break;
                case 5:
                    x -= 1;
                    y += 1;
                    break;
                case 6:
                    x -= 1;
                    break;
                case 7:
                    x -= 1;
                    y -= 1;
                    break;
            }

            if (x == 1 || x == (WIDTH - 1) || y == 6 || y == (HEIGHT - 1))
            {

            }
            else
            {
                g_bullet[empty].live = 1;
                g_bullet[empty].dir = current_dir;
                g_bullet[empty].current_move_frame = 0;
                g_bullet[empty].travel_distance = 0;
                g_bullet[empty].x = x;
                g_bullet[empty].y = y;
            }

            current_dir += 1;

            if (current_dir >= 8)
            {
                current_dir = 0;
            }
        }

        g_current_bullet_spawn_frame = 0;
        g_bullet_dir += 1;

        if (g_bullet_dir >= 8)
        {
            g_bullet_dir = 0;
        }
    }
    else
    {
        g_current_bullet_spawn_frame += 1;
    }
}

void draw_rectangle(WINDOW *win, int y1, int x1, int y2, int x2)
{
    mvwhline(win, y1, x1, 0, x2-x1);
    mvwhline(win, y2, x1, 0, x2-x1);
    mvwvline(win, y1, x1, 0, y2-y1);
    mvwvline(win, y1, x2, 0, y2-y1);
    mvwaddch(win, y1, x1, ACS_ULCORNER);
    mvwaddch(win, y2, x1, ACS_LLCORNER);
    mvwaddch(win, y1, x2, ACS_URCORNER);
    mvwaddch(win, y2, x2, ACS_LRCORNER);
}

void draw_score_UI(WINDOW *win)
{
    mvwhline(win, 6, 1, 0, WIDTH-2);
    draw_rectangle(win, 1, 2, 5, WIDTH - 3);

    wattron(win,COLOR_PAIR(5));
    switch(g_current_pow)
    {
        case 1:
            mvwprintw(win, 3, 9,"POW ■□□□□□□□");
            break;
        case 2:
            mvwprintw(win, 3, 9,"POW ■■□□□□□□");
            break;
        case 3:
            mvwprintw(win, 3, 9,"POW ■■■□□□□□");
            break;
        case 4:
            mvwprintw(win, 3, 9,"POW ■■■■□□□□");
            break;
        case 5:
            mvwprintw(win, 3, 9,"POW ■■■■■□□□");
            break;
        case 6:
            mvwprintw(win, 3, 9,"POW ■■■■■■□□");
            break;
        case 7:
            mvwprintw(win, 3, 9,"POW ■■■■■■■□");
            break;
        case 8:
            mvwprintw(win, 3, 9,"POW ■■■■■■■■");
            break;
    }
    wattroff(win,COLOR_PAIR(5));

    mvwvline(win, 2, 35, 0, 3);

    wattron(win,COLOR_PAIR(4));
    switch(g_current_spd)
    {
        case 1:
            mvwprintw(win, 3, 42,"SPD ■□□□□□□□");
            break;
        case 2:
            mvwprintw(win, 3, 42,"SPD ■■□□□□□□");
            break;
        case 3:
            mvwprintw(win, 3, 42,"SPD ■■■□□□□□");
            break;
        case 4:
            mvwprintw(win, 3, 42,"SPD ■■■■□□□□");
            break;
        case 5:
            mvwprintw(win, 3, 42,"SPD ■■■■■□□□");
            break;
        case 6:
            mvwprintw(win, 3, 42,"SPD ■■■■■■□□");
            break;
        case 7:
            mvwprintw(win, 3, 42,"SPD ■■■■■■■□");
            break;
        case 8:
            mvwprintw(win, 3, 42,"SPD ■■■■■■■■");
            break;
    }
    wattroff(win,COLOR_PAIR(4));

    mvwvline(win, 2, 68, 0, 3);

    char score[] = "SCORE 0 0 0 0 0 0";

    int score_value = g_current_score;

    score[6] = score_value/100000 +'0';
    score_value = score_value%100000;
    score[8] = score_value/10000 +'0';
    score_value = score_value%10000;
    score[10] = score_value/1000 +'0';
    score_value = score_value%1000;
    score[12] = score_value/100 +'0';
    score_value = score_value%100;
    score[14] = score_value/10 +'0';
    score_value = score_value%10;
    score[16] = score_value +'0';
    
    wattron(win,COLOR_PAIR(3));
    mvwprintw(win, 3, 75,"%s", score);
    wattroff(win,COLOR_PAIR(3));
}

void gameplay(WINDOW *win)
{
    //wclear(win);
    werase(win);

    box(win,0,0);
    
    draw_score_UI(win);

    char in = getch();

    switch(in)
    {
        case 'w':
            g_player_dir = 0;
            break;
        case 's':
            g_player_dir = 1;
            break;
        case 'a':
            g_player_dir = 2;
            break;
        case 'd':
            g_player_dir = 3;
            break;
    }
    
    if (g_current_player_move_frame >= g_player_move_frame)
    {
        switch(g_player_dir)
        {
            case 0:
                if (g_player_y > 7)
                    g_player_y -= 1;
                break;
            case 1:
                if (g_player_y < HEIGHT - 2)
                    g_player_y += 1;
                break;
            case 2:
                if (g_player_x > 2)
                    g_player_x -= 1;
                break;
            case 3:
                if (g_player_x < WIDTH - 2)
                    g_player_x += 1;
                break;
        }
        g_current_player_move_frame = 0;
    }
    else
    {
        g_current_player_move_frame += 1;
    }
    
    flushinp();

    spawn_enemy();
    enemy_move();

    spawn_bullet();
    bullet_move();

    draw_enemies(win);
    draw_player(win);
    draw_bullets(win);
    player_enemy_collision_check();
    bullet_enemy_collision_check();

    wrefresh(win);
    usleep(DELAY);
}

void initialize_colors()
{
    start_color();
    init_pair(1,COLOR_BLUE,COLOR_BLACK);
    init_pair(2,COLOR_YELLOW,COLOR_WHITE);
    init_pair(3,COLOR_MAGENTA,COLOR_BLACK);
    init_pair(4,COLOR_YELLOW,COLOR_BLACK);
    init_pair(5,COLOR_RED,COLOR_BLACK);
}