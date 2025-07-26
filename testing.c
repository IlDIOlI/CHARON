#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
int main(){
	initscr();
	printw("%d DOWN, %d UP, %d ENTER...\n",KEY_DOWN,KEY_UP,KEY_ENTER);
	getch();
	keypad(stdscr, TRUE);
	while(true){
		printw("%d, \n",getch());
	}
	endwin();
	return(0);
}