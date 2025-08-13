typedef struct {
    int port;
    int maximum_connections;
    int request_timeout_seconds;
    char *certification_path;
    char *key_path;
    bool use_ssl; 
} ServerConfig;