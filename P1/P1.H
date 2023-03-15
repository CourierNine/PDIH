#ifndef P1
#define P1


void gotoxy(int columna, int fila);
void setCursorType(int tipo_cursor);
void setVideoMode(int modo);
int getVideoMode();
void textColor(int color);
void textBackground(int color);
void clrscr();
void cputchar(char letra);
void getche();