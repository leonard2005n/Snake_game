#pragma once
#include "snake.h"

//Function that borders the playable area
void border(char v[][200], int n);

//Function that prints a frame to the screen
void print_game(char v[][200], int n, long score, snake *s);

//Function that initialize the playable area
int initialize_game (int *n, snake *s, snake *food);

//Function that returns coordinates of two values
void random_coordinates(int *x, int *y, int n);

//Function to check if a key has been pressed
int kbhit();

//Function to restore the terminal to its original state
void restore_terminal();

//Function to configure the terminal for non-canonical mode
void configure_terminal();

//Function that draws a frame
void draw(char v[][200], int n, snake *s,snake *food);

//Takes the input of the keyboard and move the snake
int input(char v[][200], int *m, snake *s, snake *food, long *score, int bot);

//Function that prints the game over screen
void game_over(long score);

//Inputs that are genereted by the bot
void input_bot(snake *s, int *m, char *c);