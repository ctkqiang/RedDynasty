#include "llm.h"

typedef struct {
    int sockfd;  
    LLM_MODEL *current_llm;
    char *pending_response;
} ClientSession;