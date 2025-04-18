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
	item_link(main_menu,create_struct_menu_init("Label_the_first\n"));
	item_link(main_menu,create_struct_menu_init("Template1\n"));
	item_link(main_menu,create_struct_menu_init("Template2\n"));
	item_link(main_menu,create_struct_menu_init("Template3\n"));
}
