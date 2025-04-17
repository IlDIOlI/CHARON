#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

//STRUCTS!
struct Menu_init {
	 char * label;
	 bool selected;
	 struct Menu_init * next;
};

struct Menu {
	struct Menu_init * head;
	int cursor_pos;
	int x,y;
};

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
		//ugly nested for loop for printing out zeroes, first loop acts for rows, second for columns in persons terminal, it will probably break however if the window is resized during process
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
//beautiful function where everything dies ig, final freeing memory and halting is done here...
void die (int in){
	endwin();
	switch(in) {
        case 0:
            printf("Normal exit\n");
            break;
        case 1:
            printf("Memory allocation failed\n");
            break;
        case 2:
            printf("String duplication failed\n");
            break;
        default:
            printf("Unknown error\n");
    }

    endwin();  // Restore terminal
    exit(in == 0 ? EXIT_SUCCESS : EXIT_FAILURE);
}

//recieves user command, halts when q is pressed
char user_in(void){
	flushinp();
	int input = getch();
    
    if (input == 'q' || input == 'Q') {
        die();
    }
    
    return (input); 
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
    //trying to implement arrow key support and everything else...
    keypad(stdscr, TRUE);
	int x,y;
	getmaxyx(stdscr,y,x);
	if ((y%2 && x%2) == 0)
	{
		move(y/2,(x/2)-6);
		printw("C.H.A.R.O.N.");
	}
	else {
	//adjusting to comfy values which can be divided by 2
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
//function for adding options to the menu in menu_main function
void option_menu(char * option){
	printw("%s\n",option);
}
//creating structs for this menu
//defacto for creating each options for the menu...
struct Menu_init * create_struct_menu_init (char * label){
	struct Menu_init *ptr;
	ptr = malloc(sizeof(struct Menu_init));
	if (ptr == NULL){
		die(1);
	}
	ptr->label = strdup(label);
	if (!ptr->label) {
        die(2);
    }
	ptr->selected = false;
	ptr->next = NULL;
	return (ptr);
	//REMEMBER TO FREE THIS SHI
}
//creating structs for menu handling
//defacto grid and simple struct for handling
struct Menu * create_struct_menu (int x,int y){
	struct Menu *ptr;
	ptr = malloc(sizeof(struct Menu));
	if (ptr == NULL){
		die(1);
	}
	ptr->head = NULL;
	ptr->cursor_pos = 0;
	ptr->x = x;
	ptr->y = y;
	return (ptr);
	//REMEMBER TO FREE THIS SHI
}
//main menu function, options with links? will be here 
void menu_main(){
//todo
	clear();
	mvprintw(4,8,"Welcome to C.H.A.R.O.N.\n");
	option_menu("Option1");
	user_in();
}
//function for handling user input in the menu and elsewhere (selecting, moving with arrow keys etc.)
/*void user_in_handle(int input){
	//handle
	//need to handle arrow key input
}*/

//NEED: function for displaying active option

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
