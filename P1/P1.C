#include<dos.h>
#include<stdio.h>

int back_color;
int color;


void gotoxy(int columna, int fila){
	union REGS inregs, outregs;

	inregs.h.ah = 2;
	inregs.h.dl = columna;
	inregs.h.dh = fila;
	inregs.h.bh = 0;

	int86(0x10, &inregs, &outregs);
}

void setCursorType(int tipo_cursor){
	union REGS inregs, outregs;

	inregs.h.ah = 0x01;
	switch(tipo_cursor){
		case 0:
				inregs.h.ch = 010;
				inregs.h.cl = 000;
				break;
		case 1:
				inregs.h.ch = 010;
				inregs.h.cl = 010;
				break;
		case 2:
				inregs.h.ch = 000;
				inregs.h.cl = 010;
				break;
	}
		int86(0x10, &inregs, &outregs);
}

void setVideoMode(int modo){
	union REGS inregs, outregs;
	inregs.h.al = modo;
	inregs.h.ah = 0x00;
	int86(0x10, &inregs, &outregs);
}

int getVideoMode(void){
	union REGS inregs, outregs;
	int modo_video;

	inregs.h.ah = 0x0F;
	int86(0x10, &inregs, &outregs);

	modo_video = outregs.h.al;

	return modo_video;
}

void cputchar(char letra){
	union REGS inregs, outregs;

	inregs.h.ah = 0x09;
	inregs.h.al = letra;
	inregs.h.bl = (color << 4) | back_color;
	inregs.h.bh = 0x00;
	inregs.x.cx = 1;

	int86(0x10, &inregs, &outregs);
}

void textColor(int unColor){
	color = unColor;
}

void textBackground(int unColor){
	back_color = unColor;
}

void clrscr(void){

	setVideoMode(3);
}

void getChe(void){
	union REGS inregs, outregs;
	char letra;

	inregs.h.ah = 0x00;

	int86(0x16, &inregs, &outregs);

	letra = outregs.h.al;

	cputchar(letra);
}

void main(){

	clrscr();

}

