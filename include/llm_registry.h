#pragma once

#include <stddef.h>
#include "llm.h"

LLM_MODEL *registry_pick_first_available(void);