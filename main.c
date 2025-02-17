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
	int n, ok = 1, bot, time;
	long score = 0;

	bot = initialize_game(&n, &s, &food);
	if (bot == 1)
		time = 100000;
	else 
		time = 400000;
	draw(board, n, &s, &food);
	print_game(board, n, score, &s);
	while (ok) {
		draw(board, n, &s, &food);
		print_game(board, n, score, &s);
		usleep(time);
		ok = input(board, &n, &s, &food, &score, bot);
	}
	game_over(score);
	restore_terminal();
	return 0;
}
