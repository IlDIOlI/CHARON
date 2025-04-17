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
