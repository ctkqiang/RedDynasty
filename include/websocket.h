#include <time.h>
#include "llm_backend.h"

typedef enum {
    WEBSOCKET_HANDSHAKE,
    WEBSOCKET_CONNECTED,
    WEBSOCKET_CLOSING,
    WEBSOCKET_CLOSED
} WebsocketState;

typedef struct {
    int id;
    WebsocketState websocket_state;
    char *client_ip;
    time_t last_activity;
    LLMBackend *current_llm_backend;
    void *llm_session;
} WebsocketConnection;