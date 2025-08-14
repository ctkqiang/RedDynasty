#include <stdlib.h>
#include <stdio.h>

#include "config.c"


int PORT = 0x1F90;


int main(int argc, char *argv[]) {
    load_env("../.env");

    const char *OPENAPI_KEY = getenv("OPENAPI_KEY");
    const char *GEMINI_KEY = getenv("OPENAPI_KEY");
    const char *CLAUDE = getenv("CLAUDE_KEY");

    if (argc > 1) PORT = atoi(argv[0x1]);

    return 0x0;
}