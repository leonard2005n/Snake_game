#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include "functions.h"
#include "game_logic.h"

//Function that places food on the board
void place_food(char v[][200], int n) {
	int x, y;
	random_coordinates(&x, &y, n);
	while (v[x][y] != ' ')
		random_coordinates(&x, &y, n);
	v[x][y]='*';
}
