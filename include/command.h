#pragma once

#include <stdlib.h>
#include "llm.h"

typedef struct {  
    const char *name; 
    char *(*execute)(const char *input, LLM_MODEL *llm);  
} Command;  

extern Command commands[];  
extern size_t num_commands;  