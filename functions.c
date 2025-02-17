#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include "functions.h"
#include "game_logic.h"
#include "snake.h"

//Function that initialize the playable area
int initialize_game(int *m, snake *s, snake *food)
{
	int n;
	char c;
	printf("You want to see a bot playing? y/N\n");
	scanf("%c", &c);

	if (c == 'y') {
		printf("Enter the size of the game (6 - 150) that is even: ");
		scanf("%d", &n);
		while (n < 6 || 150 < n || n % 2 == 0) {
			printf("Wrong value please enter a value bettween 6 and 150 that is even:");
			scanf("%d", &n);
		}
	} else {
		printf("Enter the size of the game(6 - 150): ");
		scanf("%d", &n);
		while (n < 6 || 150 < n) {
			printf("Wrong value please enter a value bettween 6 and 150:");
			scanf("%d", &n);
		}
	}
	configure_terminal();
	s->lenght = 2;
	s->body[0].x = n / 2;
	s->body[0].y = n / 2;
	s->body[1].x = n / 2 - 1;
	s->body[1].y = n / 2;
	
	//Put the food in the playable area
	int i = 0;
	while (i < 5) {
		int x, y, ok = 1;
		random_coordinates(&x, &y, n);
		for (int j = 0; j < 2; j++) {
			if (x == s->body[j].x && y == s->body[j].y)
				ok = 0;
		}
		for (int j = 0; j < i; j++) {
			if (x == food->body[j].x && y == food->body[j].y) 
				ok = 0;
		}
		if (ok == 1) {
			food->body[i].x = x;
			food->body[i].y = y;
			i++;
		}
	}
	food->lenght = 5;
	*m = n;

	if (c == 'y')
	 return 1;
	
	return 0;
}

void draw(char v[][200], int n, snake *s, snake *food)
{
	for (int i = 0; i < n + 1; i++) {
		for (int j = 0; j < n + 1; j++) {
			if (i == 0)
				v[0][j] = 'X';
			else if (j == 0)
				v[i][0] = 'X';
			else if (i == n)
				v[n][j] = 'X';
			else if (j == n)
				v[i][n] = 'X';
			else
				v[i][j] = ' ';
		}
	}

	for (int i = 0; i < 5; i++) {
		v[food->body[i].x][food->body[i].y] = '*';
	}

	v[s->body[0].x][s->body[0].y] = '@';
	for (int i = 1; i < s->lenght; i++) {
		v[s->body[i].x][s->body[i].y] = '#';
	}
}

//Function that returns coordinates of two values
void random_coordinates(int *x, int *y, int n)
{
	*x = rand() % n;
	*y = rand() % n;

	if(*x == 0)
		(*x)++;
	if(*y == 0)
		(*y)++;
}

//Function that prints a frame to the screen
void print_game(char v[][200], int n, long score, snake *s)
{
	printf("\033[H\033[J");
	printf("SCORE: %ld00\n", score);
	for (int i = 0; i < n + 1; i++) {
		printf("%s\n", v[i]);
	}
	//FOR DEBUG
	// printf("%d %d\n", s->body[0].x, s->body[0].y);
}

// Function to configure the terminal for non-canonical mode
void configure_terminal() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~(ICANON | ECHO); // Disable canonical mode and echo
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

// Function to restore the terminal to its original state
void restore_terminal() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag |= (ICANON | ECHO); // Re-enable canonical mode and echo
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

// Function to check if a key has been pressed
int kbhit() {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

//Takes the input of the keyboard and move the snake
int input(char v[][200], int *m, snake *s, snake *food, long *score, int bot)
{
	int n = *m, ok = 1;
	char c;
	static char x = 's';
	if (bot) {
		input_bot(s, &n, &c);
	} else {
		if (!kbhit()) {
			c = x;
		} else {
			c = getchar();
		}
	}
	if (c == 'w' && x != 's') {
		ok = move(s, -1, 0, food, n, score);
		x = c;
	}
	else if (c == 'd' && x != 'a') {
		ok = move(s, 0, 1, food, n, score);
		x = c;
	}
	else if (c == 's' && x != 'w') {
		ok = move(s, 1, 0, food, n, score);
		x = c;
	}
	else if (c == 'a' && x != 'd') {
		ok = move(s, 0, -1, food, n, score);
		x = c;  
	} else {
		return input(v, m, s, food, score, bot);
	}

	//FOR DEBUG
	// FILE *out = fopen("last.txt", "a");
	// fprintf(out, "%c\n", c);
	return ok;
}

//Function that prints the game over screen
void game_over(long score)
{
	printf("\033[H\033[J");
	printf("GAME OVER!\n");
	printf("SCORE: %ld00\n", score);
}

//Inputs that are genereted by the bot
void input_bot(snake *s, int *m, char *c)
{
	int n = *m;
	static int path = 0;
	static int direction  = 1;
	if (path == 0) {
		if (s->body[0].x == n - 1) {
			path = 1 ;
			*c = 'a';
			return;
		} 
		*c = 's';
		return;
	} else {
		if (s->body[0].y == n - 1 && s->body[0].x == 1) {
			path = 0;
			direction = 1;
			*c = 's';
			return;
		}
		if (direction  == 1) {
			if (s->body[0].y == 1) {
				direction = 2;
				*c = 'w';
				return;
			}
			*c = 'a';
			return;
		} else {
			if (s->body[0].y == n - 2 && s->body[0].x != 1) {
				direction = 1;
				*c = 'w';
				return;
			}
			*c = 'd';
			return;
		}
	}
}
