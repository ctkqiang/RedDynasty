CC = gcc
CFLAGS = -Wall -Wextra -O2 -Iinclude
LDFLAGS = -lcurl -lpthread

SRC = src/main.c src/server.c src/llm.c src/commands.c src/utils.c \
      backends/openai.c backends/gemini.c backends/claude.c backends/openrouter.c

OBJ = $(SRC:.c=.o)
TARGET = llm_gateway

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ) $(TARGET)