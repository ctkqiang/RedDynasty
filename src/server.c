#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <jansson.h>

#include "../include/server.h"
#include "../include/llm_registry.h"

#define BUFFER_SIZE 8192

void server_loop(int port, LLM_MODEL *backend) {
    int server_fd, client_fd;
    struct sockaddr_in addr;
    char buffer[BUFFER_SIZE];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket");
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("bind");
        close(server_fd);
        exit(1);
    }

    if (listen(server_fd, 10) < 0) {
        perror("listen");
        close(server_fd);
        exit(1);
    }

    printf("[*] 服务器正在端口 %d 启动\n", port);

    while (1) {
        client_fd = accept(server_fd, NULL, NULL);
        if (client_fd < 0) {
            perror("accept");
            continue;
        }

        ssize_t bytes = read(client_fd, buffer, BUFFER_SIZE - 1);
        if (bytes <= 0) {
            close(client_fd);
            continue;
        }
        buffer[bytes] = '\0';

        // find the start of the HTTP body
        char *body = strstr(buffer, "\r\n\r\n");
        if (!body) {
            close(client_fd);
            continue;
        }
        body += 4; // skip "\r\n\r\n"

        // parse JSON
        json_error_t err;
        json_t *root = json_loads(body, 0, &err);
        if (!root) {
            const char *msg = "{\"error\":\"Invalid JSON\"}";
            dprintf(client_fd,
                "HTTP/1.1 400 Bad Request\r\n"
                "Content-Type: application/json\r\n"
                "Content-Length: %zu\r\n\r\n%s",
                strlen(msg), msg
            );
            close(client_fd);
            continue;
        }

        json_t *prompt_json = json_object_get(root, "prompt");
        if (!json_is_string(prompt_json)) {
            const char *msg = "{\"error\":\"Missing 'prompt' field\"}";
            dprintf(client_fd,
                "HTTP/1.1 400 Bad Request\r\n"
                "Content-Type: application/json\r\n"
                "Content-Length: %zu\r\n\r\n%s",
                strlen(msg), msg
            );
            json_decref(root);
            close(client_fd);
            continue;
        }

        const char *prompt = json_string_value(prompt_json);
        char *response = NULL;

        if (backend->send_request(prompt, &response)) {
            dprintf(client_fd,
                "HTTP/1.1 200 OK\r\n"
                "Content-Type: application/json\r\n"
                "Content-Length: %zu\r\n\r\n%s",
                strlen(response), response
            );
            free(response);
        } else {
            const char *err_msg = "{\"error\":\"LLM request failed\"}";
            dprintf(client_fd,
                "HTTP/1.1 500 Internal Server Error\r\n"
                "Content-Type: application/json\r\n"
                "Content-Length: %zu\r\n\r\n%s",
                strlen(err_msg), err_msg
            );
        }

        json_decref(root);
        close(client_fd);
    }
}
