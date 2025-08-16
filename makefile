CC = gcc
CFLAGS = -Wall -Iinclude -I/usr/local/include -I/opt/homebrew/include
LDFLAGS = -L/usr/local/lib -L/opt/homebrew/lib -lcurl -ljansson 

SRC = $(wildcard src/*.c backend/*.c backend/vuln/*.c backend/command.c)
OBJ = $(SRC:.c=.o)

TARGET = main

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(OBJ) $(TARGET)
