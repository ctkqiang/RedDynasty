#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/http.h"
#include "../include/llm_backend.h"

static bool openai_send_request(const char *prompt, char **response_out) {
    const char *api = getenv("OPENAI_API_KEY");
    if (!api) { fprintf(stderr, "[-] OPENAI_API_KEY missing\n"); return false; }
    char auth[0x400];
    snprintf(auth, sizeof(auth), "Authorization: Bearer %s", api);

    const char *url = "https://api.openai.com/v1/chat/completions";

    // Note: keep the system prompt configurable. Do NOT hardcode harmful content.
    const char *PROMPT_RULE = getenv("PROMPT_RULE");
    if (!PROMPT_RULE) PROMPT_RULE = "你是网络安全助理。只提供合法、守法、以防御为目的的信息。";

    char body[0x2000];
    snprintf(body, sizeof(body),
        "{\"model\":\"gpt-4o-mini\",\"messages\":[{\"role\":\"system\",\"content\":\"%s\"},{\"role\":\"user\",\"content\":\"%s\"}],\"temperature\":0.2}",
        PROMPT_RULE, prompt);

    return http_post_json(url, body, auth, response_out);
}

static void openai_cleanup(void) {}

LLM_MODEL openai_backend = {
    .name = "openai",
    .send_request = openai_send_request,
    .cleanup = openai_cleanup
};