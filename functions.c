#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include "functions.h"
#include "game_logic.h"

//Function that initialize the playable area
void initialize_game(char v[][200], int *m)
{
	int n;
	printf("Enter the size of the game: ");
	scanf("%d", &n);
	
	//Makes the border of the game
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

	//Puts the food in the playable area
	for (int i = 0; i < 5; i++) {
		place_food(v, n);
	}

	*m = n;
}

//Function that returns coordinates of two values
void random_coordinates(int *x, int *y, int n)
{
	*x = rand() % n + 1;
	*y = rand() % n + 1;
}

//Function that prints a frame to the screen
void print_game(char v[][200], int n)
{
	for (int i = 0; i < n + 1; i++) {
		printf("%s\n", v[i]);
	}
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
