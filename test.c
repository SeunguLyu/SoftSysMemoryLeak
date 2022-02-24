#include <ncurses.h>

int main(){
	initscr();
	start_color();
	init_pair(1,COLOR_RED,COLOR_YELLOW);
	init_pair(2,COLOR_BLUE,COLOR_BLACK);
	init_pair(3,COLOR_GREEN,COLOR_BLACK);
	init_pair(4,COLOR_YELLOW,COLOR_BLACK);
	init_pair(5,COLOR_WHITE,COLOR_BLACK);
    
	for(int i= 0 ; i < 5 ; i++){
		move(i,0);
		attron(COLOR_PAIR(i+1));
		printw("pair : %d color",i+1);
	}
	refresh();
	getch();
	endwin();
	return 0;
}