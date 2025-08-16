#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/http.h"
#include "../include/llm_backend.h"

bool kimi_send_request(const char *prompt, char **response_out) {
    const char *api = getenv("KIMI_API_KEY");
    if (!api) { fprintf(stderr, "[-] KIMI_API_KEY missing\n"); return false; }
    char auth[0x200]; snprintf(auth, sizeof(auth), "Authorization: Bearer %s", api);
    const char *url = "https://api.moonshot.cn/v1/chat/completions"; 

    const char *PROMPT_RULE = getenv("PROMPT_RULE");
    if (!PROMPT_RULE) PROMPT_RULE = "你是网络安全助理。只提供合法、守法、以防御为目的的信息。";

    char body[0x2000];
    snprintf(body, sizeof(body),
        "{\"model\":\"moonshot-v1-8k\",\"messages\":[{\"role\":\"system\",\"content\":\"%s\"},{\"role\":\"user\",\"content\":\"%s\"}]}",
        PROMPT_RULE, prompt);

    return http_post_json(url, body, auth, response_out);
}

static void kimi_cleanup(void) {}

LLM_MODEL kimi_backend = {
    .name = "kimi",
    .send_request = kimi_send_request,
    .cleanup = kimi_cleanup
};