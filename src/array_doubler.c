/* Generic Array doubler */

#include <stdlib.h>
#include <stdio.h>

typedef struct generic_list {
    void ** list;
    int length;
    int values;
} LIST;

LIST * init_list(int starting_length) {
    
    LIST * list;
    list = (LIST *) malloc(1);
    if (starting_length <= 0)
        starting_length = 10; //set default length

    list->list = (void *) calloc(starting_length, sizeof(void *));
    list->length = starting_length;
    list->values = 0;

    return list;
}

LIST * append_list(LIST * list, void * value) {
    int i;
    int new_length;
    void ** tmp_ptr;
    list->values++;
    if (list->length <= list->values) { //double list
        printf("test0\n");
        new_length = list->length * 2;
        tmp_ptr = list->list;
        list->list = (void *) calloc(new_length, sizeof(void *));
        for (i=0; i<list->values; ++i)
            list->list[i] = tmp_ptr[i];
        list->length = new_length;
        free(tmp_ptr);
    }
    list->list[list->values-1] = value;
    return list;
}

int main(int argc, char *argv[])
{
    LIST * test_list;
    test_list = init_list(2);

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
}

