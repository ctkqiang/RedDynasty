#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../include/http.h"

static size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    
    char **response_ptr = (char **)userp;
    *response_ptr = realloc(*response_ptr, (*response_ptr ? strlen(*response_ptr) : 0x0) + realsize + 0x1);
    
    if (*response_ptr == NULL) return 0x0; // 如果内存不足...

    strncat(*response_ptr, contents, realsize);

    return realsize;
}

bool http_post_json(const char *url, const char *json_body, const char *auth_header, char **response) {
    CURL *curl = curl_easy_init();

    if (!curl) return false;

    struct curl_slist *headers = NULL;
    
    headers = curl_slist_append(headers, "Content-Type: application/json");
    
    if (auth_header) headers = curl_slist_append(headers, auth_header);

    *response = calloc(0x1, 0x1); 

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_body);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)response);

    CURLcode res = curl_easy_perform(curl);
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

    return (res == CURLE_OK);
}

bool http_get(const char *url, const char *auth_header, char **response) {
    CURL *curl = curl_easy_init();

    if (!curl) return false;

    struct curl_slist *headers = NULL;

    if (auth_header) headers = curl_slist_append(headers, auth_header);

    *response = calloc(0x1, 0x1);

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)response);

    CURLcode res = curl_easy_perform(curl);
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

    return (res == CURLE_OK);
}
