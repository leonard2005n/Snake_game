#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include "functions.h"
#include "game_logic.h"
#include "snake.h"

int main(void)
{
	srand(time(NULL));
	char board[200][200] = {0};
	snake s, food;
	int n, ok = 1;
	long score = 0;

	initialize_game(&n, &s, &food);
	draw(board, n, &s, &food);
		print_game(board, n, score);
	while (ok) {
		draw(board, n, &s, &food);
		print_game(board, n, score);
		usleep(225000);
		ok = input(board, &n, &s, &food, &score);
	}
	game_over(score);
	restore_terminal();
	return 0;
}
