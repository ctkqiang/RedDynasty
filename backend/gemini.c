#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/http.h"
#include "../include/llm_backend.h"

bool gemini_send_request(const char *prompt, char **response_out) {
    const char *api = getenv("GEMINI_API_KEY");
    if (!api) { 
        fprintf(stderr, "[-] GEMINI_API_KEY missing\n"); 
        return false; 
    }

    char url[0x400];

    snprintf(url, sizeof(url), 
        "https://generativelanguage.googleapis.com/v1beta/models/gemini-1.5-pro:generateContent?key=%s", 
        api);

    const char *PROMPT_RULE = getenv("PROMPT_RULE");
    
    if (!PROMPT_RULE) {
        PROMPT_RULE = "你是网络安全助理。只提供合法、守法、以防御为目的的信息。";
    }

    char body[0x2000];

    snprintf(body, sizeof(body),
        "{"
          "\"systemInstruction\":{\"parts\":[{\"text\":\"%s\"}]},"
          "\"contents\":[{\"role\":\"user\",\"parts\":[{\"text\":\"%s\"}]}]"
        "}",
        PROMPT_RULE, prompt
    );

    const char *headers[] = {
        "Content-Type: application/json",
        NULL
    };

    return http_post_json(url, body, headers, response_out);
}

static void gemini_cleanup(void) {}

LLM_MODEL gemini_backend = {
    .name = "gemini",
    .send_request = gemini_send_request,
    .cleanup = gemini_cleanup
};
