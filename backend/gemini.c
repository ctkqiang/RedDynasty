#include <curl/curl.h>
#include <string.h>
#include <stdlib.h>

#include "../include/llm.h"

void gemini_send_request(const char *prompt, char **response) {
    // ? 
}

static LLM_MODEL gemini_backend = {
    .name = "gemini",
    .send_request = gemini_send_request,
    .cleanup = NULL
};