CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Iinclude
LDFLAGS = -lncurses
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
BIN = ahorcado

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o $(BIN)

run: all
	./$(BIN)
