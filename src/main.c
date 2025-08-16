#include <stdlib.h>
#include <stdio.h>

#include "../include/config.h"
#include "../include/llm.h"
#include "../include/server.h"
#include "../include/llm_registry.h"

int PORT = 0x1F90;

int enviroment_setup(int argc, char *argv[]);

int main(int argc, char *argv[]) {
    if (enviroment_setup(argc, argv) != 0) {
        fprintf(stderr, "[-] 环境初始化失败\n");
        return EXIT_FAILURE;
    }

    printf("[*] 服务器正在端口 0x%X (%d) 启动\n", PORT, PORT);

    LLM_MODEL *backend = llm_select_model();

    if (!backend) {
        fprintf(stderr, "[-] 没有可用的 LLM backend\n");
        return EXIT_FAILURE;
    }
    printf("[+] 已选择 backend: %s\n", backend->name);

    const char *system_prompt = getenv("SYSTEM_PROMPT");
    if (!system_prompt) {
        system_prompt = "你是网络安全助理。只提供合法、守法、以防御为目的的信息。";
    }

    printf("[+] 使用的 SYSTEM_PROMPT: %s\n", system_prompt);

    char *response = NULL;
    if (backend->send_request(system_prompt, &response)) {
        printf("[LLM 回复]: %s\n", response);
        free(response);
    } else {
        fprintf(stderr, "[-] 请求失败: backend %s\n", backend->name);
    }

    if (backend->cleanup) backend->cleanup();

    server_loop(PORT, backend);
    
    return EXIT_SUCCESS;
}

int enviroment_setup(int argc, char *argv[]) {
    if (!load_env(".env")) {
        fprintf(stderr, "[-] 加载 .env 文件失败\n");
        return 1;
    }

    const char *OPENAI_KEY     = getenv("OPENAI_KEY");
    const char *GEMINI_KEY     = getenv("GEMINI_KEY");
    const char *CLAUDE_KEY     = getenv("CLAUDE_KEY");
    const char *DEEPSEEK_KEY   = getenv("DEEPSEEK_KEY");
    const char *QWEN_KEY       = getenv("QWEN_KEY");
    const char *GROK_KEY       = getenv("GROK_KEY");           
    const char *OPENROUTER_KEY = getenv("OPENROUTER_API_KEY"); 
    const char *KIMI_KEY       = getenv("KIMI_KEY");    

    if (!OPENAI_KEY && !GEMINI_KEY && !CLAUDE_KEY &&
        !DEEPSEEK_KEY && !QWEN_KEY && !GROK_KEY &&
        !OPENROUTER_KEY && !KIMI_KEY) 
    {
        fprintf(stderr, "[-] 缺少所有 API 密钥，至少需要一个\n");
        return 2;
    }

    if (OPENAI_KEY)     printf("[*] OPENAI_KEY found\n");
    if (GEMINI_KEY)     printf("[*] GEMINI_KEY found\n");
    if (CLAUDE_KEY)     printf("[*] CLAUDE_KEY found\n");
    if (DEEPSEEK_KEY)   printf("[*] DEEPSEEK_KEY found\n");
    if (QWEN_KEY)       printf("[*] QWEN_KEY found\n");
    if (GROK_KEY)       printf("[*] GROK_KEY found\n");
    if (OPENROUTER_KEY) printf("[*] OPENROUTER_API_KEY found\n");
    if (KIMI_KEY)       printf("[*] KIMI_KEY found\n");

    if (argc > 1) {
        PORT = atoi(argv[1]);
        if (PORT <= 0 || PORT > 65535) {
            fprintf(stderr, "[-] 无效端口号: %s\n", argv[1]);
            return 3;
        }
    }

    return 0;
}
