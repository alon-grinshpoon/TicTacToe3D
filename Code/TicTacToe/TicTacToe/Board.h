#pragma once
// Includes
#include <irrlicht.h> // Irrlicht h.file
#include <stdlib.h>
#include <time.h>	
// Static Variables
#define BOARD_SIZE 3

class Board
{
public:
	static Board* getInstance() { return &boardInstance; }
	irr::core::vector3df getEmptySlot();
	void setSlot(int row, int column, int player);
	bool checkWin();

private:
	static Board boardInstance;
	int board[BOARD_SIZE][BOARD_SIZE];
};
