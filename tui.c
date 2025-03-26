#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
//intro animation
int init(void){
	int x,y,m_delay;
	m_delay = 10000;
	initscr();
	getmaxyx(stdscr,y,x);	
	refresh();
	//debug values for determining terminal properties
	//printw("Y value: %i\n",y);
	//printw("X value: %i\n",x);
	//debug getch
	//getch();
	clear();
	for (int i = 0; i < y; ++i)
	{
		for (int i = 0; i < x; ++i)
			{
			//can be more variable
			printw("0");
			usleep(m_delay);
			refresh();
		}
		m_delay = m_delay * 0.5;
	}
	sleep(1);
	return 0;
}

int die (void){
	endwin();
}
//recieves user command, halts when q is pressed
char user_in(void){
	char *input = (char *)malloc(sizeof(char));
	*input = (char)getch();
	if (input == NULL) {
        printf("Catasthropic error happened!\n");
        exit(1);
    }
	if(*input == 0x71){
		exit(0);
	} else {
		return(*input);
	}
	/*refresh();
	mvprintw(0,0,"point: %p\n input:%c\n",*input,input);
	refresh();
	getch();*/
}
//slow printw with char as a input and int as delay...
void epic_printw(const char *input, int e_delay){
	for (int i = 0; input[i]!='\0'; ++i)
	{
		printw("%c",input[i]);
		refresh();
		usleep(e_delay);
	}
	refresh();
}
//fancy welcoming screen
int menu_init (void){
	clear();
	cbreak();    
    noecho();
    //trying to implement arrow key support
    keypad(stdscr, TRUE);
	int x,y;
	getmaxyx(stdscr,y,x);
	if ((y%2 && x%2) == 0)
	{
		move(y/2,(x/2)-6);
		printw("C.H.A.R.O.N.");
	}
	else {
		if (x%2 == 0){
			y--;
		}
		if (y%2 == 0){
			x--;
		}
		move(y/2,(x/2)-6);
		printw("C.H.A.R.O.N.");
	}
	move((y/2)+1,(x/2)-15);
	epic_printw("Press any key to continue...", 40000);
}
//main menu function
void menu_main(){
//todo
	clear();
	mvprintw(4,8,"Welcome to C.H.A.R.O.N.\n");
	user_in();
}
//function for adding options to the menu
/*option_menu(const char *option){
//todo
}
*/
void user_in_handle(int input){
	//handle
	//need to handle arrow key input
}
//NEED: function for displaying active option, function for handling user input
//for testing, will be moved to main.c
int main(void)
{
	init();
	menu_init();
	user_in();
	menu_main();
	die();
	return 0;
}