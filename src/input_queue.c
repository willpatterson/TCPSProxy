#include "include/connection_queue.h"

typedef struct connection {
    int socketfd;
    char * buffer;
} Connection;

typedef struct connection_node {
    ConnectionNode * previous; 
    Connection * conn;
} Connection_node;

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

int enqueue(ConnectionQueue * conn_queue, ConnectionNode * conn) {
    if ((conn == NULL) || (conn_queue == NULL)) return 1;
    conn->previous = NULL;

    int queue_len = conn_queue->length + 1;

    if (queue_len > conn_queue->max_length)
        return 2;
    else if (queue_len == 1)
        conn_queue->front = conn;
    conn_queue->end = conn;
    return 0;
}

Connection * dequeue(ConnectionQueue * conn_queue) {
    if ((conn_queue == NULL) || (conn_queue->front == NULL)) return NULL;

    ConnectionNode * front_conn;
    front_conn = conn_queue->front;
    conn_queue->front = front_conn->previous;
    return front_conn->conn;
}

int main(int argc, char *argv[])
{

}
