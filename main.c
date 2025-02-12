#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "functions.h"
#include "game_logic.h"
#include "snake.h"

int main(void)
{
	srand(time(NULL));
	char board[MAX][MAX] = {0};
	snake s, food;
	int n;

	initialize_game(board, &n, &s, &food);
	draw(board, n, &s, &food);
		print_game(board, n);
	while (1) {
		draw(board, n, &s, &food);
		print_game(board, n);
		input(board, &n, &s, &food);
	}
	restore_terminal();
	return 0;
}
