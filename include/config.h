#pragma once
#include <stdbool.h>

typedef struct {
    int port;
    int maximum_connections;
    int request_timeout_seconds;
    char *certification_path;
    char *key_path;
    bool use_ssl; 
} ServerConfig;

bool load_env(const char *filename);

const char *getenv_fallback(const char *key, const char *fallback);