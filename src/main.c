#include <stdlib.h>
#include <stdio.h>

#include "config.c"

int PORT = 0x1F90;

int main(int argc, char *argv[]) {
    enviroment_setup(argc, argv);
    
    printf("[*] Server starting on port 0x%X (%d)\n", PORT, PORT);

    return 0x0;
}

void enviroment_setup(int argc, char *argv[]) {
    if (!load_env(".env")) {
        fprintf(stderr, "[-] Failed to load .env file\n");
        return 0x1;
    }

    const char *OPENAI_KEY = getenv("OPENAI_KEY");
    const char *GEMINI_KEY = getenv("GEMINI_KEY");
    const char *CLAUDE_KEY = getenv("CLAUDE_KEY");
    // TODO add more

    if (!OPENAI_KEY && !GEMINI_KEY && !CLAUDE_KEY) {
        fprintf(stderr, "[-] Missing all API keys, at least one required\n");
        return 0x2;
    }

    if (OPENAI_KEY) printf("[*] OPENAI_KEY found\n");
    if (GEMINI_KEY) printf("[*] GEMINI_KEY found\n");
    if (CLAUDE_KEY) printf("[*] CLAUDE_KEY found\n");

    if (argc > 0x1) PORT = atoi(argv[0x1]);
}