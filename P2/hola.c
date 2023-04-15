#include<ncurses.h>

int main(){
	initscr();
	printw("Hola");
	refresh();
	getch();
	endwin();
	
	return 0;
}
