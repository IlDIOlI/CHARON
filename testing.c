#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
/*void menu_setup(void){
	//setup the menu here, so I can call the function in the main just with structs defined.
	int x,y;
	getmaxyx(stdscr,y,x);
	//moving so the first hardcoded text is displayed correctly
	move(5,10);
	x=x-10;
	y=y-5;
	struct Menu *main_menu = create_struct_menu(x,y);
	//the menu is defined and is waiting for some adding options.
	//Options are added here:
	item_link(main_menu,create_struct_menu_init("Label_the_first\n"));
	item_link(main_menu,create_struct_menu_init("Template1\n"));
	item_link(main_menu,create_struct_menu_init("Template2\n"));
	item_link(main_menu,create_struct_menu_init("Template3\n"));
	menu_render(main_menu);
}
*/
/*int user_in(void){
	flushinp();
	int input = getch();

    if (input == 'q' || input == 'Q') {
				//die(0);
				exit(0);
    }

    return (input);
}
*/
int main(){
	int i = 1;
	initscr();
	cbreak();
	keypad(stdscr, TRUE);
	int input = getch();
	if(input==KEY_DOWN){
		mvprintw(0,0,"Down key!\n");
		printf("DOWN!\n");
	} else {
		mvprintw(0,0,"Not a down key\n");
	}

	while(i == 1){
		move(0,0);
		refresh();
	}
	endwin();
	return 0;
}

void user_in_handle(int input,struct Menu * menu){
	//need to handle up, down, enter (maybe left and right? for nested menu options...);
}
