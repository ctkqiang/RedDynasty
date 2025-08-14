CC = gcc
CFLAGS = -Wall -Wextra -O0 -g -Iinclude
LDFLAGS = -lcurl

# 源文件
SRC = src/main.c \
      src/llm.c \
      src/server.c \
      backend/openai.c \
      backend/gemini.c \
      backend/deepseek.c \
      backend/kimi.c \
      backend/qwen.c

TARGET = llmchat

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
	@echo "[*] Build complete: $(TARGET)"

clean:
	rm -f $(TARGET)
	@echo "[*] Clean done"
