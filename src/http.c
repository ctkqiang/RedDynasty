#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#include "../include/http.h"

struct write_result {
    char *data;
    size_t size;
};

static size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct write_result *mem = (struct write_result *)userp;

    char *ptr = realloc(mem->data, mem->size + realsize + 1);
    if (!ptr) return 0;

    mem->data = ptr;
    memcpy(&(mem->data[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->data[mem->size] = 0;

    return realsize;
}

bool http_post_json(const char *url, const char *json_body, const char *auth_header, char **response_out) {
    CURL *curl = curl_easy_init();
    if (!curl) return false;

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    if (auth_header) headers = curl_slist_append(headers, auth_header);

    struct write_result chunk = { malloc(1), 0 };

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_body);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

    CURLcode res = curl_easy_perform(curl);

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK) {
        free(chunk.data);
        return false;
    }

    *response_out = chunk.data;
    return true;
}

bool http_get(const char *url, const char *auth_header, char **response_out) {
    CURL *curl = curl_easy_init();
    if (!curl) return false;

    struct curl_slist *headers = NULL;
    if (auth_header) headers = curl_slist_append(headers, auth_header);

    struct write_result chunk = { malloc(1), 0 };

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

    CURLcode res = curl_easy_perform(curl);

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK) {
        free(chunk.data);
        return false;
    }

    *response_out = chunk.data;
    return true;
}
