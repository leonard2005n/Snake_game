#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>
#include "functions.h"
#include "game_logic.h"
#include "snake.h"

// Function that places food on the board
void place_food(snake *food, snake *s, int n, int i) {
	int ok  = 0;
	while (!ok) {
		int x, y;
		ok = 1;
		random_coordinates(&x, &y, n);
		for (int j = 0; j < s->lenght; j++) {
			if (x == s->body[j].x && y == s->body[j].y)
				ok = 0;
		}
		for (int j = 0; j < 5; j++) {
			if (x == food->body[j].x && y == food->body[j].y) 
				ok = 0;
		}
		if (ok == 1) {
			food->body[i].x = x;
			food->body[i].y = y;
		}
	}
}

//Move the snake
void move(snake *s, int x, int y, snake *food, int n)
{
	if (food_colision(s, x, y, food, n)) {
		s->lenght++;
	}
	for (int i = s->lenght - 1; i > 0; i--) {
		s->body[i] = s->body[i - 1];
	}
	s->body[0].x += x;
	s->body[0].y += y;
}

//See if the snake colided with the food
int food_colision(snake *s, int x, int y, snake *food, int n)
{
	x += s->body[0].x;
	y += s->body[0].y;

	for (int i = 0; i < 5; i++) {
		if (x == food->body[i].x && y == food->body[i].y) {
			if (food->lenght + s->lenght + 1 <= (n - 1) * (n - 1)) {
				place_food(food, s, n, i);
			}
			else {
				food->body[i].x = n + 5;
				food->body[i].y = n + 5;
				food->lenght--;
			}
			return 1;
		}
	}
	return 0;
}