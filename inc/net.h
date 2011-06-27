#ifndef SERVER_H
#define SERVER_H

#include <limits.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

typedef struct client {    
    int sockfd;
    struct sockaddr_in addr;
} client_t;

struct server;

typedef int(*filter_t)(struct server*, client_t*, char*, char*);

typedef struct server {
    int listenfd;
    struct sockaddr_in addr;
    
    int port;
    char dir[PATH_MAX];
    char** index_files;
    int index_files_length;
    
    filter_t* filters;
    int filters_length;
    
    client_t* current;
    void(*handler)(struct server*, client_t*);
} server_t;

server_t* create_server(
    int port, char* dir,
    char** index_files, int index_files_length,
    filter_t* filters, int filters_length,
    void(*handler)(server_t*, client_t*));
void free_server(server_t* server);

void server_accept_loop(server_t* server);

#endif