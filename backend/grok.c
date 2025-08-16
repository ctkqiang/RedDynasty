#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/http.h"
#include "../include/llm_backend.h"

static bool grok_send_request(const char *prompt, char **response_out) {
    const char *api = getenv("GROK_API_KEY");
    if (!api) { fprintf(stderr, "[-] GROK_API_KEY missing\n"); return false; }
    char auth[0x200]; snprintf(auth, sizeof(auth), "Authorization: Bearer %s", api);
    const char *url = "https://api.x.ai/v1/chat/completions"; // example

    const char *PROMPT_RULE = getenv("PROMPT_RULE");
    if (!PROMPT_RULE) PROMPT_RULE = "你是网络安全助理。只提供合法、守法、以防御为目的的信息。";

    char body[0x2000];
    snprintf(body, sizeof(body),
        "{\"model\":\"grok-2-mini\",\"messages\":[{\"role\":\"system\",\"content\":\"%s\"},{\"role\":\"user\",\"content\":\"%s\"}]}",
        PROMPT_RULE, prompt);

    return http_post_json(url, body, auth, response_out);
}

static void grok_cleanup(void) {}

LLM_MODEL grok_backend = {
    .name = "grok",
    .send_request = grok_send_request,
    .cleanup = grok_cleanup
};