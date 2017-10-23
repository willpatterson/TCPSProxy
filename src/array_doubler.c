/* Generic Array doubler 
 * TODO:
 *   delete function
 *   generic print/display functionallity
 *   remove tests
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
LIST * append_list(LIST * list, void * value) {
    int i;
    int new_length;
    void ** tmp_ptr;
    list->end++;
    if (list->length <= list->end) { //double list
        printf("test0\n");
        new_length = list->length * 2;
        tmp_ptr = list->list;
        list->list = (void *) calloc(new_length, sizeof(void *));
        for (i=0; i<list->end; ++i)
            list->list[i] = tmp_ptr[i];
        list->length = new_length;
        free(tmp_ptr);
    }
    list->list[list->end-1] = value;
    return list;
}

/* Returns 0 if removed, 1 if error */
int list_remove_item(LIST * list, int index) {
    int i;
    int new_length;
    void ** tmp_ptr;

    if (index >= list->end)
        return 1;

    free(list->list[index]);
    list->end = list->end - 1;
    if (list->end >= list->length/4) { // shrink array
        tmp_ptr = list->list;
        new_length = list->length/2;
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

    test_list = append_list(test_list, test_value);
    printf("%d\n", *(int *)(test_list->list[0]));

    test_list = append_list(test_list, test_value2);
    printf("%d\n", *(int *)(test_list->list[0]));
    printf("%d\n", *(int *)(test_list->list[1]));

    test_list = append_list(test_list, test_value3);
    test_list = append_list(test_list, test_value4);
    test_list = append_list(test_list, test_value5);
    test_list = append_list(test_list, test_value6);
    printf("%d\n", *(int *)(test_list->list[5]));
    //test_list = append_list(test_list, test_value2);
    return 0;
}

