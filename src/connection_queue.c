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

    int queue_len = conn_queue->length + 1;

    if (queue_len > conn_queue->max_length)
        return 2;
    else if (queue_len == 1)
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

int display_connection_queue(ConnectionQueue * conn_queue) {}
int display_connection(Connection * conn) {}

int free_connection_queue(ConnectionQueue * conn_queue) {}
int free_connection(Connection * conn) {}
