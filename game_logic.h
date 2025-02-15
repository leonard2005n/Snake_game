#pragma once

// Function that places food on the board
void place_food(snake *food, snake *s, int n, int i);

//The game "engine"
void game(char v[][200], int n, snake *s);

//Move the snake
int move(snake *s, int x, int y, snake *food, int n, long *score);

//See if the snake colided with the food
int food_collision(snake *s, int x, int y, snake *food, int n);

//See if the snake colided with someting to trigger a game over
int obstacle_collision(snake *s, int x, int y, int n);
