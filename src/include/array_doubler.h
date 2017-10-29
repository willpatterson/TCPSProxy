#include <stdlib.h>
#include <stdio.h>

typedef struct generic_list {
    void ** list;
    int length;
    int end;
} LIST;


LIST * init_list(int starting_length);
int append_list(LIST * list, void * value);
int list_insert_item(LIST * list, void * value, int insert_after);
int list_remove_item(LIST * list, int index);
int list_delete_item(LIST * list, int index);
void free_list(LIST * list);
