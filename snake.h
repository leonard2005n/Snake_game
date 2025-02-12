#pragma once
#define MAX 500

typedef struct {
	int x, y;
} position;

//A struc for the position of the snake
typedef struct {
	int lenght;
	position body[MAX];
} snake;

