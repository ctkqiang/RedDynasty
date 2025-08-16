#include "../include/llm.h"
#include "../include/llm_backend.h"

extern LLM_MODEL openai_backend;
extern LLM_MODEL gemini_backend;
extern LLM_MODEL qwen_backend;
extern LLM_MODEL kimi_backend;
extern LLM_MODEL claude_backend;
extern LLM_MODEL openrouter_backend;

LLM_MODEL *available_llm[] = {
    &openai_backend,
    &gemini_backend,
    &qwen_backend,
    &kimi_backend
};

size_t num_llm = sizeof(available_llm) / sizeof(available_llm[0]);
