/* Common Variables and Structs */

typedef struct backend_server {
    char * address;
    int port;
    char * polocy;
} BACKEND_SERVER;

typedef struct backend {
    char * name;
    BACKEND_SERVER * backend_servers;
} BACKEND;

typedef struct frontend {
    char * address;
    int port;
    int conqueue;
    char * backend_name;
} FRONTEND;


