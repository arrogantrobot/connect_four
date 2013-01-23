#include "Board.h"
#include <string.h>

Board::Board() {
	player open = OPEN;
	player * p = &open;	
	int num = sizeof(player) * HEIGHT * WIDTH;
	for (int x = 0; x < WIDTH; x++)
		for(int y = 0; y < HEIGHT; y++)
			board[x][y] = OPEN;
}

Board::~Board() {

}

player Board::getPosition(int x, int y) const {
	return board[x][y];
}

