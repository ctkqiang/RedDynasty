#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/llm_registry.h"

extern LLM_MODEL *available_llm[];
extern size_t num_llm;

LLM_MODEL *llm_select_model(void) {
    if (getenv("GEMINI_API_KEY")) return get_llm_model_by_name("gemini"); 

    for (size_t i = 0; i < num_llm; i++) {
        if (getenv(available_llm[i]->name)) {
            return available_llm[i];
        }
    }

    fprintf(stderr, "[-] 没有找到任何 LLM API KEY\n");
    exit(3);
}



LLM_MODEL *get_llm_model_by_name(const char *name) {
    for (size_t i = 0; i < num_llm; i++) {
        if (strcmp(available_llm[i]->name, name) == 0) {
            return available_llm[i];
        }
    }
    return NULL;
}


LLM_MODEL *registry_pick_first_available(void) {
    return num_llm ? available_llm[0] : NULL;
}
