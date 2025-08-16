#pragma once

#include <sys/socket.h>
#include "llm.h"

#define MAX_CLIENTS 100
#define BUFFER_SIZE 4096

typedef struct {
    int sockfd;
    LLM_MODEL *llm;
    char buffer[BUFFER_SIZE];
} Client;

void run_server(int port);
void server_loop(int port, LLM_MODEL *backend);
