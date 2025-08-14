#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "../include/http.h"
#include "../include/llm.h"

static bool deepseek_send_request(const char *prompt, char **response) {
    const char *url = "https://api.deepseek.com/v1/chat/completions";
    const char *api_key = getenv("DEEPSEEK_API_KEY");
    
    if (!api_key) {
        fprintf(stderr, "在 .env 中缺少 DEEPSEEK_API_KEY\n");
        return false;
    }

    char auth_header[0x100];
    snprintf(auth_header, sizeof(auth_header), "Authorization: Bearer %s", api_key);

    char body[0x400];
    snprintf(body, sizeof(body), "{\"model\": \"deepseek-chat\", \"messages\":[{\"role\":\"user\",\"content\":\"%s\"}]}", prompt);

    return http_post_json(url, body, auth_header, response);
}

static void deepseek_cleanup(void) {}

LLM_MODEL deepseek_backend = {
    .name = "deepseek",
    .send_request = deepseek_send_request,
    .cleanup = deepseek_cleanup
};
