#include <curl/curl.h>
#include <string.h>
#include <stdlib.h>

#include "../include/llm.h"

static size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata) {
    char **response = userdata;
    
    size_t total = size * nmemb;
    *response = realloc(*response, total + 1);
    
    memcpy(*response, ptr, total);
    (*response)[total] = '\0';

    return total;
}

static bool openai_send_request(const char *prompt, char **response) {
    CURL *curl = curl_easy_init();
    if (!curl) return false;

    *response = NULL;
    struct curl_slist *headers = NULL;
    
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, "Authorization: Bearer YOUR_API_KEY");

    char postfields[1024];
    snprintf(postfields, sizeof(postfields),
             "{\"model\":\"gpt-3.5-turbo\",\"messages\":[{\"role\":\"user\",\"content\":\"%s\"}]}",
             prompt);

    curl_easy_setopt(curl, CURLOPT_URL, "https://api.openai.com/v1/chat/completions");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postfields);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);

    CURLcode res = curl_easy_perform(curl);
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

    return res == CURLE_OK && *response != NULL;
}

static LLM_MODEL openai_backend = {
    .name = "openai",
    .send_request = openai_send_request,
    .cleanup = NULL
};