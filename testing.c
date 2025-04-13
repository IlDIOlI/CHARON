struct create_struct_menu_init (char * label){
	int * ptr;
	struct Menu_init Menu_init;
	Menu_init.label = strdup(label);
	Menu_init.selected = false;
	Menu_init.next = NULL;
	*ptr = malloc(sizeof(struct Menu_init));
	return (ptr):
}
int* create_struct_menu (int x,y){
	struct Menu Menu;
	int Menu.head = NULL;
	int Menu.cursor_pos = 0;
	int Menu.x = x;
	int Menu.y = y;
	*ptr = malloc(sizeof(struct Menu));
	return (ptr);
}
