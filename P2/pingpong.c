#include <ncurses.h>
#include <unistd.h>

#define DELAY 30000

int main(int argc, char *argv[]){
	int x = 2, y = 2;
	int palo_dch = 1, palo_izq = 1;
	int next_x = 0;
	int next_y = 0;
	int direction_x = 1;
	int direction_y = 1;
	int cols, rows;
	int ch;
	int points_izq = 0, points_dch = 0;
	
	initscr();
	noecho();
	nodelay(stdscr, TRUE);
	keypad(stdscr, TRUE);
	curs_set(FALSE);
	
	while(1){
		clear();
		
		getmaxyx(stdscr, rows, cols);
		
		ch = getch();
		
		if(ch==KEY_UP && palo_dch!=1){
			palo_dch-=1;
		}
		else if(ch==KEY_DOWN && palo_dch!=rows-2){
			palo_dch+=1;
		}	
		else if(ch=='w' && palo_izq!=1){
			palo_izq-=1;
		}
		else if(ch=='s' && palo_izq!=rows-2){
			palo_izq+=1;
		}
		
		mvprintw(rows/5, cols/2-20, "%d", points_izq);
		mvprintw(rows/5, cols/2+20, "%d", points_dch);
		
		mvprintw(palo_izq-1, 1, "|");
		mvprintw(palo_izq, 1, "|");
		mvprintw(palo_izq+1, 1, "|");
		
		mvprintw(palo_dch-1, cols-1, "|");
		mvprintw(palo_dch, cols-1, "|");
		mvprintw(palo_dch+1, cols-1, "|");
		
		mvprintw(rows/2-2, cols/2, "|");
		mvprintw(rows/2-1, cols/2, "|");
		mvprintw(rows/2, cols/2, "|");
		mvprintw(rows/2+1, cols/2, "|");
		mvprintw(rows/2+2, cols/2, "|");
		
		mvprintw(y, x, "o");
		
		
		refresh();
		usleep(DELAY);
		
		next_x = x + direction_x;
		next_y = y + direction_y;
		
		if((next_x >= cols-1 && (next_y==palo_dch || next_y==palo_dch-1 || next_y==palo_dch+1 ))  || (next_x < 1 && (next_y==palo_izq || next_y==palo_izq-1 || next_y==palo_izq+1 ))){
			direction_x*= -1;
		}
		else if(next_x >= cols || next_x < 0){
			y = rows/2;
			x = cols/2;
			direction_x*= -1;
			if(next_x >= cols){
				points_izq+=1;
			}
			if(next_x < 0){
				points_dch+=1;
			}
		}
		else{
			x+=direction_x;
		}
		
		if(next_y >= rows || next_y < 0){
			direction_y*= -1;
		}
		else{
			y+=direction_y;
		}
	}
	
	endwin();
}
