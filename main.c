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
	int n;

	initialize_game(board, &n, &s, &food);
	draw(board, n, &s, &food);
		print_game(board, n);
	while (1) {
		draw(board, n, &s, &food);
		print_game(board, n);
		usleep(225000); // Sleep for 100 milliseconds
		input(board, &n, &s, &food);
	}
	restore_terminal();
	return 0;
}
