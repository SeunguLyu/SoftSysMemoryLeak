#include <time.h>
#include <ncurses.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define WIDTH 100
#define HEIGHT 40

int g_gameStatus = 0;

int g_playerDir = -1;
int g_curX = WIDTH/2;
int g_curY = HEIGHT/2;

int g_userMoveFrame = 5;
int g_currentUserMoveFrame = 0;

char logo[][300] = {
    "███╗░░░███╗███████╗███╗░░░███╗░█████╗░██████╗░██╗░░░██╗██╗░░░░░███████╗░█████╗░██╗░░██╗",
    "████╗░████║██╔════╝████╗░████║██╔══██╗██╔══██╗╚██╗░██╔╝██║░░░░░██╔════╝██╔══██╗██║░██╔╝",
    "██╔████╔██║█████╗░░██╔████╔██║██║░░██║██████╔╝░╚████╔╝░██║░░░░░█████╗░░███████║█████═╝░",
    "██║╚██╔╝██║██╔══╝░░██║╚██╔╝██║██║░░██║██╔══██╗░░╚██╔╝░░██║░░░░░██╔══╝░░██╔══██║██╔═██╗░",
    "██║░╚═╝░██║███████╗██║░╚═╝░██║╚█████╔╝██║░░██║░░░██║░░░███████╗███████╗██║░░██║██║░╚██╗",
    "╚═╝░░░░░╚═╝╚══════╝╚═╝░░░░░╚═╝░╚════╝░╚═╝░░╚═╝░░░╚═╝░░░╚══════╝╚══════╝╚═╝░░╚═╝╚═╝░░╚═╝",
};

void gameplay(WINDOW *win)
{
    werase(win);
    box(win,0,0);

    char in = getch();

    switch(in)
    {
        case 'w':
            g_playerDir = 0;
            break;
        case 's':
            g_playerDir = 1;
            break;
        case 'a':
            g_playerDir = 2;
            break;
        case 'd':
            g_playerDir = 3;
            break;
    }
    
    if (g_currentUserMoveFrame == g_userMoveFrame)
    {
        switch(g_playerDir)
        {
            case 0:
                g_curY -= 1;
                break;
            case 1:
                g_curY += 1;
                break;
            case 2:
                g_curX -= 1;
                break;
            case 3:
                g_curX += 1;
                break;
        }
        g_currentUserMoveFrame = 0;
    }
    else
    {
        g_currentUserMoveFrame += 1;
    }
    
    flushinp();
    mvwprintw(win, 1, 1,logo[0]);
    wattron(win,COLOR_PAIR(1));
    mvwprintw(win, g_curY, g_curX,"@");
    wattroff(win,COLOR_PAIR(1));

    wrefresh(win);
    usleep(10000);
}

int main(int argc, char *argv[]) 
{
    setlocale(LC_ALL, "");
    int max_y = 0, max_x = 0;
    initscr();
    cbreak();
	noecho();             
	keypad(stdscr, TRUE); 
	curs_set(0); 
    nodelay(stdscr, 1);

    start_color();
    init_pair(1,COLOR_RED,COLOR_YELLOW);

    srand(time(NULL));

    getmaxyx(stdscr, max_y, max_x);

    WINDOW *win = newwin(HEIGHT,WIDTH,max_y/2-HEIGHT/2, max_x/2-WIDTH/2);

    while(1)
    {
        gameplay(win);
    }

	getch();
	endwin();
	return 0;
}