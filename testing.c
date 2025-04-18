void item_link(struct Menu * menu_ptr,struct Menu_init * menu_in_ptr){
		//link the head and next to each other
		menu_ptr->head = menu_in_ptr;
}
void menu_setup(void){
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
	struct Menu_init *first_option = create_struct_menu_init("Label_the_first");
	struct Menu_init *second_option = create_struct_menu_init("Second_label...");
	item_link(main_menu,first_option);
}