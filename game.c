#include <time.h>
#include <ncurses.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define WIDTH 100
#define HEIGHT 40

struct Enemy
{
    int x;
    int y;
};

int g_terminal_y = 0, g_terminal_x = 0;

int g_game_status = 0;
int g_title_selection = 0;

int g_player_dir = -1;
int g_player_x = WIDTH/2;
int g_player_y = HEIGHT/2;

int g_player_move_frame = 10;
int g_current_player_move_frame = 0;

struct Enemy g_enemies[1000];

char logo[][300] = {

    "███╗░░░███╗███████╗███╗░░░███╗░█████╗░██████╗░██╗░░░██╗██╗░░░░░███████╗░█████╗░██╗░░██╗",
    "████╗░████║██╔════╝████╗░████║██╔══██╗██╔══██╗╚██╗░██╔╝██║░░░░░██╔════╝██╔══██╗██║░██╔╝",
    "██╔████╔██║█████╗░░██╔████╔██║██║░░██║██████╔╝░╚████╔╝░██║░░░░░█████╗░░███████║█████═╝░",
    "██║╚██╔╝██║██╔══╝░░██║╚██╔╝██║██║░░██║██╔══██╗░░╚██╔╝░░██║░░░░░██╔══╝░░██╔══██║██╔═██╗░",
    "██║░╚═╝░██║███████╗██║░╚═╝░██║╚█████╔╝██║░░██║░░░██║░░░███████╗███████╗██║░░██║██║░╚██╗",
    "╚═╝░░░░░╚═╝╚══════╝╚═╝░░░░░╚═╝░╚════╝░╚═╝░░╚═╝░░░╚═╝░░░╚══════╝╚══════╝╚═╝░░╚═╝╚═╝░░╚═╝",
};

char gameover[][300] = {
    
    "░██████╗░░█████╗░███╗░░░███╗███████╗░█████╗░██╗░░░██╗███████╗██████╗░",
    "██╔════╝░██╔══██╗████╗░████║██╔════╝██╔══██╗██║░░░██║██╔════╝██╔══██╗",
    "██║░░██╗░███████║██╔████╔██║█████╗░░██║░░██║╚██╗░██╔╝█████╗░░██████╔╝",
    "██║░░╚██╗██╔══██║██║╚██╔╝██║██╔══╝░░██║░░██║░╚████╔╝░██╔══╝░░██╔══██╗",
    "╚██████╔╝██║░░██║██║░╚═╝░██║███████╗╚█████╔╝░░╚██╔╝░░███████╗██║░░██║",
    "░╚═════╝░╚═╝░░╚═╝╚═╝░░░░░╚═╝╚══════╝░╚════╝░░░░╚═╝░░░╚══════╝╚═╝░░╚═╝",
};

char description[][100] = {
    "A long time ago in a SoftSys class far, far away...",
    "An Oliner decided to finish their project in a single day...",
    "It worked perfectly on the day it was presented...",
    "Without knowing that the memory was leaking!!!",
    "You accidentally compiled the program...",
    "And now you have to free all the leaking memories!"
};

char selection[][30] = {
    "Start Game",
    "Exit Game",
    "Press W,A,S,D to move",
    "Press Enter to Select",
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
        mvwprintw(win, 5+i, 7, logo[i]);
    }
    wattroff(win,COLOR_PAIR(3));

    for (int i = 0; i<6; i++)
    {
        int xpos = (WIDTH - strlen(description[i]))/2;
        mvwprintw(win, 14+2*i, xpos, description[i]);
    }

    int xpos = (WIDTH - strlen(selection[2]))/2;
    wattron(win,COLOR_PAIR(1));
    mvwprintw(win, 27, xpos, selection[2]);
    xpos = (WIDTH - strlen(selection[3]))/2;
    mvwprintw(win, 29, xpos, selection[3]);
    wattroff(win,COLOR_PAIR(1));
    
    if (g_title_selection == 0)
    {
        int xpos = (WIDTH - strlen(selection[0]))/2;
        wattron(win,COLOR_PAIR(2));
        mvwprintw(win, 32, xpos, selection[0]);
        wattroff(win,COLOR_PAIR(2));
        wattron(win,COLOR_PAIR(4));
        xpos = (WIDTH - strlen(selection[1]))/2;
        mvwprintw(win, 34, xpos, selection[1]);
        wattroff(win,COLOR_PAIR(4));
    }
    else
    {
        int xpos = (WIDTH - strlen(selection[0]))/2;
        wattron(win,COLOR_PAIR(4));
        mvwprintw(win, 32, xpos, selection[0]);
        wattroff(win,COLOR_PAIR(4));
        xpos = (WIDTH - strlen(selection[1]))/2;
        wattron(win,COLOR_PAIR(2));
        mvwprintw(win, 34, xpos, selection[1]);
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

void resize()
{
    clear();
    mvprintw(1, 1, "Please resize the terminal and re-run the program");
    mvprintw(2, 1, "The size should be at least 100 columns and 40 lines");
    refresh();
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
                g_player_y -= 1;
                break;
            case 1:
                g_player_y += 1;
                break;
            case 2:
                g_player_x -= 1;
                break;
            case 3:
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

    wattron(win,COLOR_PAIR(1));
    mvwprintw(win, g_player_y, g_player_x,"⚇");
    wattroff(win,COLOR_PAIR(1));

    wrefresh(win);
    usleep(10000);
}

void player_enemy_collision_check()
{
    
}

void initialize_colors()
{
    start_color();
    init_pair(1,COLOR_BLUE,COLOR_BLACK);
    init_pair(2,COLOR_YELLOW,COLOR_WHITE);
    init_pair(3,COLOR_MAGENTA,COLOR_BLACK);
    init_pair(4,COLOR_YELLOW,COLOR_BLACK);
}

int main(int argc, char *argv[]) 
{
    setlocale(LC_ALL, "");
    initscr();
    cbreak();
	noecho();             
	keypad(stdscr, TRUE); 
	curs_set(0); 
    nodelay(stdscr, 1);

    initialize_colors();

    srand(time(NULL));

    getmaxyx(stdscr, g_terminal_y, g_terminal_x);

    WINDOW *win;

    if (g_terminal_x < WIDTH || g_terminal_y < HEIGHT)
    {
        nodelay(stdscr, 0);
        resize();
    }
    else
    {
        win = newwin(HEIGHT,WIDTH,g_terminal_y/2-HEIGHT/2, g_terminal_x/2-WIDTH/2);
        g_game_status = 1;
    }

    while(g_game_status > 0)
    {
        getmaxyx(stdscr, g_terminal_y, g_terminal_x);
        mvwin(win,g_terminal_y/2-HEIGHT/2, g_terminal_x/2-WIDTH/2);

        if (g_game_status == 1)
        {
            title(win);
        }
        else if (g_game_status == 2)
        {
            gameplay(win);
        }
    }

	getch();
	endwin();
	return 0;
}