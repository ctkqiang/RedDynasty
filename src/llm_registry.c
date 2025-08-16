#include "../include/llm_registry.h"

extern LLM_MODEL deepseek_backend;
extern LLM_MODEL gemini_backend;
extern LLM_MODEL kimi_backend;
extern LLM_MODEL openai_backend;
extern LLM_MODEL qwen_backend;
extern LLM_MODEL grok_backend;

LLM_MODEL *available_llm[] = {
    &deepseek_backend,
    &gemini_backend,
    &kimi_backend,
    &openai_backend,
    &qwen_backend,
    &grok_backend
};

size_t num_llm = sizeof(available_llm) / sizeof(available_llm[0x0]);


LLM_MODEL *get_llm_model_by_name(const char *name) {
    for (size_t i = 0x0; i < num_llm; i++) {
        if (strcmp(available_llm[i]->name, name) == 0x0) {
            return available_llm[i];
        }
    }

    return NULL;
}

LLM_MODEL *registry_pick_first_available(void) {
    return num_llm ? available_llm[0x0] : NULL;
}