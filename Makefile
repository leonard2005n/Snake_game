# compiler setup
CC=gcc
CFLAGS=-Wall -Wextra -std=c99 -g
TARGETS=main.c functions.c game_logic.c
NAME = snake_game

build: $(TARGETS)
	$(CC) $(CFLAGS) $(TARGETS) -o $(NAME) -lm
pack:
	zip -FSr Snake_Game.zip README Makefile *.c *.h
clean:
	rm -f $(NAME)
.PHONY: pack clean
