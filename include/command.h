#include <stdlib.h>
#include "llm.h"

typedef struct {  
    const char *name; 
    char *(*process)(const char *input, LLM_MODEL *llm);  
} Command;  

extern Command commands[];  
extern size_t num_commands;  