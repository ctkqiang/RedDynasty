#pragma once

#include <stdbool.h>

bool http_post_json(const char *url, const char *json_body, const char *auth_header, char **response);
bool http_get(const char *url, const char *auth_header, char **response);
