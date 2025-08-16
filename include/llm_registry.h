#ifndef LLM_REGISTRY_H
#define LLM_REGISTRY_H

#include <stddef.h>
#include "llm.h"
#include "llm_backend.h"

LLM_MODEL *get_llm_model_by_name(const char *name);
LLM_MODEL *registry_pick_first_available(void);
LLM_MODEL *llm_select_model(void);

extern LLM_MODEL *available_llm[];
extern size_t num_llm;

#endif
