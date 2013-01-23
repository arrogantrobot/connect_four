#ifndef __BOARD_H__
#define __BOARD_H__

#define HEIGHT 6
#define WIDTH 7

typedef enum {
	OPEN,
	PLAYER_ONE,
	PLAYER_TWO
} player;

class Board {
public:
	Board();
	~Board();
	player getPosition(int x, int y) const;
	

private:
	player board[WIDTH][HEIGHT];
};

#endif
