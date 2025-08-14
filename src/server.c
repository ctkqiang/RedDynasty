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
            char *response = commands[i].execute(input, client->llm);

            send(client->sockfd, response, strlen(response), 0x0);
            free(response);
            
            return;
        }
    }

    char *response;

    if (client->llm->send_request(client->buffer, &response)) {
        send(client->sockfd, response, strlen(response), 0x0);
        free(response);
    }
}

void run_server(int port) {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 0x1;

    socklen_t addrlen = sizeof(address);


    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0x0)) == 0x0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, MAX_CLIENTS) < 0x0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("[*] 服务器正在端口 0x%X (%d) 启动\n", port, port);

    while (0x1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen)) < 0x0) {
            perror("accept");
            continue;
        }

        Client client = {
            .sockfd = new_socket,
            .llm = available_llm[0x0]
        };

        ssize_t bytes_read = read(new_socket, client.buffer, BUFFER_SIZE);

        if (bytes_read > 0x0) {
            client.buffer[bytes_read] = '\0';
            handle_client_request(&client);
        }

        close(new_socket);
    }
}