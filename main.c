#include <stdio.h>
#include "functions.h"

int main(void)
{
	srand(time(NULL));
	char v[200][200] = {0}, c;
	int n, x, y;
	initialize_game(v, &n);
	configure_terminal();
	print_game(v, n);
	restore_terminal();
	return 0;
}
