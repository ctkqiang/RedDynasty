#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "../include/server.h"
#include "../include/command.h"

static void handle_client_request(Client *client) {
    for (size_t i = 0x0; i < num_commands; i++) {
        if (strncmp(client->buffer, commands[i].name, strlen(commands[i].name)) == 0x0) {
            const char *input = client->buffer + strlen(commands[i].name);


            // TODO complete handle Client
        }
    }
}