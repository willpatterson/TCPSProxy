/* Generic Array doubler 
 * TODO:
 *   generic print/display functionallity
 *   function to merge lists
 */

#include <stdlib.h>
#include <stdio.h>

typedef struct generic_list {
    void ** list;
    int length;
    int end;
} LIST;

/* List init fuction. Returns list with an empty allocated array
 * of void pointers of default size 10
 */
LIST * init_list(int starting_length) {
    
    LIST * list;
    list = (LIST *) malloc(1);
    if (starting_length <= 0)
        starting_length = 10; //set default length

    list->list = (void *) calloc(starting_length, sizeof(void *));
    list->length = starting_length;
    list->end = 0;

    return list;
}


/* Append to end of list */
int append_list(LIST * list, void * value) {
    int i;
    int new_length;
    void ** tmp_ptr;
    if (list == NULL) return 1;
    list->end++;
    if (list->length <= list->end) { //double list
        new_length = list->length * 2;
        tmp_ptr = list->list;
        list->list = (void *) calloc(new_length, sizeof(void *));
        for (i=0; i<list->end; ++i)
            list->list[i] = tmp_ptr[i];
        list->length = new_length;
        free(tmp_ptr);
    }
    list->list[list->end-1] = value;
    return 0;
}

int list_insert_item(LIST * list, void * value, int insert_after) {
    int i;
    int new_length;
    void ** tmp_ptr;
    if (list == NULL); return 1;
    if (insert_after >= list->end) return 1;
    if (insert_after == list->end-1) {
        append_list(list, value);
        return 0;
    }

    list->end++;
    if (list->length <= list->end) { //double list
        new_length = list->length * 2;
        tmp_ptr = list->list;
        list->list = (void *) calloc(new_length, sizeof(void *));
        for (i=0; i<=insert_after; ++i)
            list->list[i] = tmp_ptr[i];
        list->list[insert_after+1] = value;
        for (i=insert_after+1; i<=list->end; ++i)
            list->list[i] = tmp_ptr[i];
        list->length = new_length;
        free(tmp_ptr);
    }

    for (i=insert_after+1; i<=list->end; ++i)
        list->list[i+1] = list->list[i];
    list->list[insert_after+1] = value;
    return 0;
}

/* Deletes item and shifts list
 * Returns 0 if removed, 1 if error */
int list_remove_item(LIST * list, int index) {
    int i;
    int new_length;
    void ** tmp_ptr;

    if (index >= list->end)
        return 1;

    free(list->list[index]);
    list->end = list->end - 1;
    if (list->end <= list->length/4) { // shrink array
        tmp_ptr = list->list;
        new_length = list->length/2;
        list->length = new_length;
        list->list = (void *) calloc(new_length, sizeof(void *));
        for (i=0; i<index; ++i)
            list->list[i] = tmp_ptr[i];
        for (i=index; i<list->end-1; ++i)
            list->list[i] = tmp_ptr[i+1];
        free(tmp_ptr);
    }
    else {
        for (i=index; i<list->end-1; ++i)
            list->list[i] = list->list[i+1];
    }
    return 0;
}

/* deletes item but doesn't shfit list
 * Returns 0 if removed, 1 if error */
int list_delete_item(LIST * list, int index) {
    if (list == NULL) return 1;
    if (index >= list->end) return 1;
    free(list->list[index]);
    list->list[index] = NULL;
    return 0;
}

/* Frees all items in a list including the list but not the list structure 
 * Not sure if this should free the list structure in addition to the items in the list 
 * Currently you must free the list then free the structure. Example:
 *     free_list(list);
 *     free(list);
 */
void free_list(LIST * list) {
    int i;
    if (list == NULL) return;
    for (i=0; i<list->end; ++i)
        free(list->list[i]);
    free(list->list);
}

int main(int argc, char *argv[])
{
    // TESTS:
    LIST * test_list;
    test_list = init_list(2);

    // Insert Tests:
    int * test_value;
    test_value = (int*) calloc(1, sizeof(int));
    *test_value = 1111;

    int * test_value2;
    test_value2 = (int*) calloc(1, sizeof(int));
    *test_value2 = 2222;

    int * test_value3;
    test_value3 = (int*) calloc(1, sizeof(int));
    *test_value3 = 3333;

    int * test_value4;
    test_value4 = (int*) calloc(1, sizeof(int));
    *test_value4 = 4444;

    int * test_value5;
    test_value5 = (int*) calloc(1, sizeof(int));
    *test_value5 = 5555;

    int * test_value6;
    test_value6 = (int*) calloc(1, sizeof(int));
    *test_value6 = 6666;

    append_list(test_list, test_value);
    printf("%d\n", *(int *)(test_list->list[0]));

    append_list(test_list, test_value2);
    printf("%d\n", *(int *)(test_list->list[0]));
    printf("%d\n", *(int *)(test_list->list[1]));

    append_list(test_list, test_value3);
    append_list(test_list, test_value4);
    append_list(test_list, test_value5);
    append_list(test_list, test_value6);
    printf("%d\n", *(int *)(test_list->list[5]));
    free_list(test_list);
    free(test_list);

    // Removal Tests

    int i;
    int list_lenght = 8;
    printf("\nREMOVE TESTS\n");
    LIST * remove_test_list;
    remove_test_list = init_list(2);

    int * tmp_ptr;
    for (i=0; i<list_lenght; ++i) {
        tmp_ptr = (int*) calloc(1, sizeof(int));
        *tmp_ptr = i;
        append_list(remove_test_list, tmp_ptr);
        printf("APPEND ITEM: %d\n", i);
    }

    printf("\n");
    printf("END: %d\n", remove_test_list->end);
    printf("\n");
    
    for (i=list_lenght; i>=list_lenght/4; --i) {
        printf("REMOVE ITEM: %d\n", i);
        list_remove_item(remove_test_list, i);
    }

    printf("\n");
    printf("END: %d\n", remove_test_list->end);
    printf("LENGTH: %d\n", remove_test_list->length);
    printf("\n");

    for (i=0; i<remove_test_list->end; ++i) {
        printf("i: %d\n", i);
        printf("%d\n", *(int *)(remove_test_list->list[i]));
    }
    free_list(remove_test_list);
    free(remove_test_list);

    // Deletion Test
    printf("\nDELETE TESTS\n");
    LIST * delete_test_list;
    delete_test_list = init_list(2);
    
    int * test_delete;
    int result;
    test_delete = (int*) calloc(1, sizeof(int));
    *test_delete= 6666;
    append_list(delete_test_list, test_delete);
    result = list_delete_item(delete_test_list, 0);
    if ((result == 0) && (delete_test_list->list[0] == NULL))
        printf("SUCCESS\n");
    free_list(delete_test_list);
    free(delete_test_list);

    return 0;
}

