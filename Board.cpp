#include "Board.h"
#include <assert.h>
#include <string.h>

Board::Board() {
	player open = OPEN;
	player * p = &open;	
	int num = sizeof(player) * HEIGHT * WIDTH;
	for (int x = 0; x < WIDTH; x++)
		rowCount[x] = 0;
		for(int y = 0; y < HEIGHT; y++)
			board[x][y] = OPEN;
}

Board::~Board() {

}

player Board::getPosition(int x, int y) const {
	assert(x >= 0);
	assert(x < WIDTH);
	assert(y >= 0);
	assert(y < HEIGHT);
	return board[x][y];
}

bool Board::playAt(int x, player p1) {
	if (!canPlay(x))
		return false;
	board[x][rowCount[x]] = p1;
	rowCount[x]++;
	return true;
}

bool Board::canPlay(int x) const {
	return rowCount[x] < HEIGHT;	
}
