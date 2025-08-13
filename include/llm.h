#include <stdlib.h> 

typedef struct {
    const char *name;
    bool (*send_request)(const char *prompt, char **response);  
} LLM_MODEL;

extern LLM_MODEL *available_llm[];
extern size_t num_llm;