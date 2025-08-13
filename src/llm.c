#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../include/llm.h"

static LLM_MODEL openai = {
    .name = "openai",
    .send_request = openai_send_request
};

static LLM_MODEL gemini = {
    .name = "gemini",
    .send_request = gemini_send_request
};

static LLM_MODEL qwen = {
    .name = "qwen",
    .send_request = qwen_send_request
};

static LLM_MODEL kimi = {
    .name = "kimi",
    .send_request = kimi_send_request
};

static LLM_MODEL claude = {
    .name = "claude",
    .send_request = claude_send_request
};

static LLM_MODEL openrouter = {
    .name = "openrouter",
    .send_request = openrouter_send_request
};

static bool openai_send_request(const char *prompt, char **response) {
    char *formatted = malloc(strlen(prompt) + 0x32);
    
    sprintf(formatted, "[OpenAI] %s", prompt);
    *response = formatted;

    return true;
}

static bool gemini_send_request(const char *prompt, char **response) {
    char *formatted = malloc(strlen(prompt) + 0x32);
    
    sprintf(formatted, "[Gemini] %s", prompt);
    *response = formatted;

    return true;
}

static bool qwen_send_request(const char *prompt, char **response) {
    char *formatted = malloc(strlen(prompt) + 0x32);
    
    sprintf(formatted, "[Qwen] %s", prompt);
    *response = formatted;

    return true;
}

static bool kimi_send_request(const char *prompt, char **response) {
    char *formatted = malloc(strlen(prompt) + 0x32);

    sprintf(formatted, "[Kimi] %s", prompt);
    *response = formatted;
    
    return true;
}

static bool claude_send_request(const char *prompt, char **response) {
    char *formatted = malloc(strlen(prompt) + 0x32);

    sprintf(formatted, "[Claude] %s", prompt);
    *response = formatted;
    
    return true;
}

static bool openrouter_send_request(const char *prompt, char **response) {
    char *formatted = malloc(strlen(prompt) + 0x32);

    sprintf(formatted, "[OpenRouter] %s", prompt);
    *response = formatted;
    
    return true;
}

LLM_MODEL *available_models [] = {
    &openai,
    &gemini,
    &qwen,
    &kimi,
    &claude,
    &openrouter
};

size_t num_llms = sizeof(available_models) / sizeof(available_models[0x0]);
