#include "../include/llm_registry.h"

extern LLM_MODEL deepseek_backend;
extern LLM_MODEL gemini_backend;
extern LLM_MODEL kimi_backend;
extern LLM_MODEL openai_backend;
extern LLM_MODEL qwen_backend;

LLM_MODEL *available_llm[] = {
    &deepseek_backend,
    &gemini_backend,
    &kimi_backend,
    &openai_backend,
    &qwen_backend
};

size_t num_llm = sizeof(available_llm) / sizeof(available_llm[0]);


LLM_MODEL *get_llm_backend(const char *name) {
    if (strcmp(name, "openai") == 0) return &openai_backend;
    if (strcmp(name, "gemini") == 0) return &gemini_backend;
    return NULL;
}