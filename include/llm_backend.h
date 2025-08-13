#include <stdlib.h> 

typedef struct {
    char *model_name;
    bool (*init) (void *config);
    char *(*generate) (const char *prompt, void *options);
    void (*cleanup) (void);
    void *configuration;
} LLMBackend;

typedef struct {
    LLMBackend *LLM_backends;
    size_t llm_backend_count;
    size_t LLM_backend_capacity;
} LLMBackendRegistry;