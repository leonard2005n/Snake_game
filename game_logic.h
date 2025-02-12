#pragma once

// Function that places food on the board
void place_food(snake *food, snake *s, int n, int i);

//The game "engine"
void game(char v[][200], int n, snake *s);

//Move the snake
void move(snake *s, int x, int y, snake *food, int n);

//See if the snake colided with the food
int food_colision(snake *s, int x, int y, snake *food, int n);