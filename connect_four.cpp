#include "Board.h"
#include <stdio.h>

void displayBoard(const Board &b) {
	for (int y = HEIGHT - 1; y >= 0; y--) {
		for (int x = 0; x < WIDTH; x++) {
			printf("%d ", b.getPosition(x,y));
		}
		printf("\n");
	}
}

int main(int argc, char *argv[]) {
	Board b;
	displayBoard(b);
	return 0;
}
