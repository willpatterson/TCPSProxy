#include "include/connection_queue.h"

typedef struct connection {
    int socketfd;
    char * buffer;
} Connection;

typedef struct connection_node {
    ConnectionNode * previous; 
    Connection * conn;
} ConnectionNode;

typedef struct connection_queue {
    ConnectionNode * end;
    ConnectionNode * front;
    int length;
    int max_length;
} ConnectionQueue;

ConnectionQueue * init_queue(int max_length) {
    ConnectionQueue * conn_queue;
    conn_queue = (ConnectionQueue *) malloc(1);
    conn_queue->end = NULL;
    conn_queue->front = NULL;
    conn_queue->length = 0;
    conn_queue->max_length = max_length;
    return conn_queue;
}

int enqueue(ConnectionQueue * conn_queue, Connection * conn) {
    if ((conn == NULL) || (conn_queue == NULL)) return 1;
    ConnectionNode * new_conn_node;
    new_conn_node = (ConnectionNode *) malloc(1);
    new_conn_node->previous = NULL;
    new_conn_node->conn = conn;

    ++conn_queue->length;

    if (conn_queue->length > conn_queue->max_length)
        return 2;
    else if (conn_queue->length == 1)
        conn_queue->front = new_conn_node;
    else
        conn_queue->end->previous = new_conn_node;
    conn_queue->end = new_conn_node;
    return 0;
}

Connection * dequeue(ConnectionQueue * conn_queue) {
    if ((conn_queue == NULL) || (conn_queue->front == NULL)) return NULL;

    ConnectionNode * front_conn_node;
    Connection * front_conn;
    front_conn_node = conn_queue->front;
    conn_queue->front = front_conn_node->previous;
    front_conn = front_conn_node->conn;
    free(front_conn_node);
    return front_conn;
}

int display_connection_queue(ConnectionQueue * conn_queue) {
    if (conn_queue == NULL) return 1;

    printf("FRONT:\n");
    printf("-------------------\n");

    int count = 0;
    ConnectionNode * current = conn_queue->front;
    while (current != NULL) {
        printf("Num: %d\n", count);
        display_connection(current->conn);
        current = current->previous;
        printf("-------------------\n");
        ++count;
    }

    printf("DONE\n");
    return 1;
}

int display_connection(Connection * conn) {
    if (conn == NULL) return 1;
    printf("Buffer   : %s\n", conn->buffer);
    printf("Socketfd : %d\n", conn->socketfd);
    return 0;
}

int free_connection_queue(ConnectionQueue * conn_queue) {}
int free_connection(Connection * conn) {} 

int main(int argc, char *argv[]) {
    Connection * conn1;
    conn1 = (Connection *) malloc(1);
    conn1->socketfd = 1;
    conn1->buffer = (char *) malloc(6);
    strcpy(conn1->buffer, "test1");

    Connection * conn2;
    conn2 = (Connection *) malloc(1);
    conn2->socketfd = 2;
    conn2->buffer = (char *) malloc(6);
    strcpy(conn2->buffer, "test2");

    Connection * conn3;
    conn3 = (Connection *) malloc(1);
    conn3->socketfd = 3;
    conn3->buffer = (char *) malloc(6);
    strcpy(conn3->buffer, "test3");

    ConnectionQueue * conn_queue;
    conn_queue = init_queue(10);
    enqueue(conn_queue, conn1);
    enqueue(conn_queue, conn2);
    enqueue(conn_queue, conn3);

    display_connection_queue(conn_queue);
}
