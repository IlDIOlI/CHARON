#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//STRUCTS!
struct Menu_init {
	 char * label;
	 struct Menu_init * next;
};

struct Menu {
	struct Menu_init * head;
	struct Menu_init * tail;
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
    if (in == 0) {
    	printf("Exit succesfully...\n");
    	exit(EXIT_SUCCESS);
    } else {
    	printf("Critical Error, EXITING...\n");
    	exit(EXIT_FAILURE);
    }
}

//recieves user command, halts when q is pressed
int user_in(void){
	flushinp();
	int input = getch();

    if (input == 'q' || input == 'Q') {
        die(0);
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
	ptr->tail = NULL;
	ptr->cursor_pos = 0;
	ptr->x = x;
	ptr->y = y;
	return (ptr);
	//REMEMBER TO FREE THIS SHI
}
void item_link(struct Menu * menu_ptr,struct Menu_init * menu_in_ptr){
		//link the head and next to each other
		menu_in_ptr->next = NULL;
		if(menu_ptr->head == NULL){
			//linking the first item and menu with head and tail...
			menu_ptr->head = menu_in_ptr;
			menu_ptr->tail = menu_in_ptr;
		} else {
			//linking every other item, but not sure about the last one...
			//UPDATE! It doesn't matter which is it, because next is set only for previous item, not the last one.
			menu_ptr->tail->next = menu_in_ptr;
			menu_ptr->tail = menu_in_ptr;
		}
}
//renders menu...
void menu_render(struct Menu * menu){
	printw("\n");
	//empty menu returns nothing and ends function
	if(menu->head == NULL){
		return;
	}
	//temp var for checking if it is in scope
	struct Menu_init *temp = menu->head;
	int selected = 0;
	while(temp != NULL){
		//highlighting and printing the selected item
		if(selected == menu->cursor_pos){
			attron(A_STANDOUT);
		}
		//printing the item
		if(temp->next==NULL){
			printw("%s",temp->label);
		} else {
			printw("%s\n",temp->label);
		}
		//elevate onto the next item
		if(selected == menu->cursor_pos){
			attroff(A_STANDOUT);
		}
		temp = temp->next;
		selected++;
	}
	refresh();
}
struct Menu * menu_setup(void){
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
	return(main_menu);
}
//function for handling user input in the menu and elsewhere (selecting, moving with arrow keys etc.)
int user_in_handle(struct Menu * menu){
	keypad(stdscr, TRUE);
	cbreak();
  noecho();
	//need to handle arrow key input and return key
	int input;
	struct Menu_init *init = menu->head;

	int menu_size = 0;
	while (init){
		menu_size++;
		init=init->next;
	}
	while(true){
		curs_set(0);
		int input = user_in();
		if (input == KEY_DOWN){
			if(menu->cursor_pos != menu_size-1){
				menu->cursor_pos++;
			}
		} else if(input == KEY_UP){
			if(menu->cursor_pos > 0){
				menu->cursor_pos--;
			}
		} else if(input == KEY_ENTER){
			//execute...
			//OR open item for more options...
			return(0);
		}
		move(5,10);
		menu_render(menu);
	}
	return(1);
}
//main menu function, options with links? will be here
void menu_main(){
//todo
	clear();
	mvprintw(4,8,"Welcome to C.H.A.R.O.N.\n");
	refresh();
	menu_setup();
	user_in_handle(menu_setup());
}
//for testing, will be moved to main.c
int main(void)
{
	init();
	menu_init();
	user_in();
	menu_main();
	die(0);
	return 0;
}
