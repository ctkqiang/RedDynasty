#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/llm_registry.h"

LLM_MODEL gemini = { .name = "gemini" };
LLM_MODEL openai = { .name = "openai" };

LLM_MODEL *available_llm[] = { &gemini, &openai };
size_t num_llm = 2;

LLM_MODEL *llm_select_model_test(void) {
    if (getenv("GEMINI_KEY")) return &gemini;
    if (getenv("OPENAI_KEY")) return &openai;
    return NULL;
}

void assert_equal_str(const char *expected, const char *actual, const char *test_name) {
    if (expected && actual && strcmp(expected, actual) == 0) {
        printf("[通过] %s\n", test_name);
    } else {
        printf("[失败] %s: 预期 '%s', 实际 '%s'\n", test_name, expected, actual ? actual : "NULL");
    }
}

int main(void) {
    setenv("GEMINI_KEY", "fakekey", 1);
    unsetenv("OPENAI_KEY");
    LLM_MODEL *m1 = llm_select_model_test();
    assert_equal_str("gemini", m1 ? m1->name : NULL, "GEMINI_KEY 优先测试");

    unsetenv("GEMINI_KEY");
    setenv("OPENAI_KEY", "fakekey", 1);
    LLM_MODEL *m2 = llm_select_model_test();
    assert_equal_str("openai", m2 ? m2->name : NULL, "OPENAI_KEY 测试");

    unsetenv("GEMINI_KEY");
    unsetenv("OPENAI_KEY");
    LLM_MODEL *m3 = llm_select_model_test();
    if (m3 == NULL) {
        printf("[通过] 无 Key 测试\n");
    } else {
        printf("[失败] 无 Key 测试: 预期 NULL, 实际 %s\n", m3->name);
    }

    return 0;
}
