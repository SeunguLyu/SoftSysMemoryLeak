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

    spawn_enemy();

    getmaxyx(stdscr, g_terminal_y, g_terminal_x);

    WINDOW *main_window;

    if (g_terminal_x < WIDTH || g_terminal_y < HEIGHT)
    {
        nodelay(stdscr, 0);
        resize();
    }
    else
    {
        main_window = newwin(HEIGHT,WIDTH,g_terminal_y/2-HEIGHT/2, g_terminal_x/2-WIDTH/2);
        g_game_status = 1;
    }

    while(g_game_status > 0)
    {
        getmaxyx(stdscr, g_terminal_y, g_terminal_x);

        if (g_game_status == 1)
        {
            title(main_window);
        }
        else if (g_game_status == 2)
        {
            gameplay(main_window);
        }
        else if (g_game_status == 3)
        {
            gameover(main_window);
        }
    }
    
	endwin();
	return 0;
}