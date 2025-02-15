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
int move(snake *s, int x, int y, snake *food, int n, long *score)
{
	if (food_collision(s, x, y, food, n)) {
		s->lenght++;
		*score += 1;
	}

	if (obstacle_collision(s, x, y, n)) {
		return 0;
	}

	for (int i = s->lenght - 1; i > 0; i--) {
		s->body[i] = s->body[i - 1];
	}
	s->body[0].x += x;
	s->body[0].y += y;
	return 1;
}

//See if the snake colided with the food
int food_collision(snake *s, int x, int y, snake *food, int n)
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

//See if the snake colided with someting to trigger a game over
int obstacle_collision(snake *s, int x, int y, int n)
{
	x += s->body[0].x;
	y += s->body[0].y;

	if (x == 0 || y == 0)
		return 1;
	
	if (x == n || y == n)
		return 1;

	for (int i = 1 ; i < s->lenght; i++) {
		if (x == s->body[i].x && y == s->body[i].y)
			return 1;
	}

	return 0;
}
