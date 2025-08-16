#pragma once
#pragma once
#include <stdbool.h>
#include "../include/llm.h"


extern LLM_MODEL openai_backend;
extern LLM_MODEL gemini_backend;
extern LLM_MODEL qwen_backend;
extern LLM_MODEL kimi_backend;
extern LLM_MODEL claude_backend;
extern LLM_MODEL openrouter_backend;

bool openai_send_request(const char *prompt, char **response_out);
bool gemini_send_request(const char *prompt, char **response_out);
bool qwen_send_request(const char *prompt, char **response_out);
bool kimi_send_request(const char *prompt, char **response_out);
bool claude_send_request(const char *prompt, char **response_out);
bool openrouter_send_request(const char *prompt, char **response_out);
