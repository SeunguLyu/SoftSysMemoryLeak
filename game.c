#include <time.h>
#include <ncurses.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 80
#define HEIGHT 30

int main(int argc, char *argv[]) 
{
    int posx = 5;
    int posy = 5;
    initscr();
    cbreak();
	noecho();             
	keypad(stdscr, TRUE); 
	curs_set(0); 
    nodelay(stdscr, 1);

    srand(time(NULL));

    WINDOW *win = newwin(HEIGHT,WIDTH,5, 5);

    int dir = -1;
    int curx = 1;
    int cury = 1;
    int blink = 0;

    int targetf = 5;
    int currentf = 0;

    while(1)
    {
        werase(win);
        box(win,0,0);

        char in = getch();

        switch(in)
        {
            case 'w':
                dir = 0;
                break;
            case 's':
                dir = 1;
                break;
            case 'a':
                dir = 2;
                break;
            case 'd':
                dir = 3;
                break;
        }
        
        if (currentf == targetf)
        {
            switch(dir)
            {
                case 0:
                    cury -= 1;
                    break;
                case 1:
                    cury += 1;
                    break;
                case 2:
                    curx -= 1;
                    break;
                case 3:
                    curx += 1;
                    break;
            }
            currentf = 0;
        }
        else
        {
            currentf += 1;
        }
        
        flushinp();
	    mvwprintw(win, cury, curx,"@");

        if (blink == 1)
        {
            mvwprintw(win, 3, 3,"!");
            blink = 0;
        }
        else
        {
            blink = 1;
        }
        wrefresh(win);
        usleep(10000);
    }

	getch();
	endwin();
	return 0;
}