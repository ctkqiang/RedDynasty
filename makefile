CC = gcc
CFLAGS = -Wall -Iinclude -I/usr/local/include -I/opt/homebrew/include
LDFLAGS = -L/usr/local/lib -L/opt/homebrew/lib -lcurl -ljansson 

SRC = $(wildcard src/*.c backend/*.c backend/vuln/*.c backend/command.c)
OBJ = $(SRC:.c=.o)

TARGET = main

UNITY_DIR = test/Unity
UNITY_SRC = $(UNITY_DIR)/src/unity.c

test: $(OBJ) $(UNITY_SRC) test/test_main.c test/test_deepseek.c
	$(CC) $(CFLAGS) -I$(UNITY_DIR)/src -o $@ $^ $(LDFLAGS)
	./test

# 原有目标保持不变
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(OBJ) $(TARGET)
