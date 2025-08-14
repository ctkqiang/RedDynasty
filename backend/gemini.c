#include <curl/curl.h>
#include <string.h>
#include <stdlib.h>

#include "../include/llm.h"

static bool gemini_send_request(const char *prompt, char **response) {
    CURL *curl = curl_easy_init();
    if (!curl) return false;

    // Similar to OpenAI but with Gemini API endpoint
    // Implement actual Gemini API call here
    *response = strdup("[Gemini] Mock response");
    curl_easy_cleanup(curl);
    return true;
}

static LLM_MODEL gemini_backend = {
    .name = "gemini",
    .send_request = gemini_send_request,
    .cleanup = NULL
};