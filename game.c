#include "game.h"

int g_terminal_y = 0, g_terminal_x = 0;

int g_game_status = 0;
int g_title_selection = 0;

int g_player_dir = -1;
int g_player_x = WIDTH/2;
int g_player_y = HEIGHT/2;

int g_player_move_frame = 10;
int g_current_player_move_frame = 0;
int g_player_attack_frame = 50;
int g_current_player_attack_frame = 0;

struct Enemy g_enemies[1000];

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
    usleep(10000);
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
    usleep(10000);
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
    for (int i = 0; i < 1; i++)
    {
        mvwprintw(win, g_enemies[i].y, g_enemies[i].x,"Ⓜ");
    }
    wattroff(win,COLOR_PAIR(5));
}

void player_enemy_collision_check()
{
    for (int i = 0; i < 1; i++)
    {
        if (g_enemies[i].x == g_player_x && g_enemies[i].y == g_player_y)
        {
            g_game_status = 3;
        }
    }
}

void gameplay(WINDOW *win)
{
    //wclear(win);
    werase(win);
    box(win,0,0);

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
    
    if (g_current_player_move_frame == g_player_move_frame)
    {
        switch(g_player_dir)
        {
            case 0:
                if (g_player_y > 1)
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

    draw_enemies(win);
    draw_player(win);
    player_enemy_collision_check();

    wrefresh(win);
    usleep(10000);
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