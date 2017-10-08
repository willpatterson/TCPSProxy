#include <stdlib.h>
#include <strings.h>
#include <string.h>

typedef struct connection Connection;
typedef struct connection_queue ConnectionQueue;

ConnectionQueue * init_queue(int max_length);
int enqueue(ConnectionQueue * conn_queue, Connection * conn);
Connection * dequeue(ConnectionQueue * conn_queue);
