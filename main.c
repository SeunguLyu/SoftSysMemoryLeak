#include "game.h"

extern int g_terminal_y;
extern int g_terminal_x;

extern int g_game_status;

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
        else if (g_game_status == 3)
        {
            gameover(win);
        }
    }

	getch();
	endwin();
	return 0;
}