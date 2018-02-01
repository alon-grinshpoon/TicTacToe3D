#pragma once
// Includes
#include <irrlicht.h> // Irrlicht h.file
#include <stdlib.h>
#include <time.h>	
// Static Variables
#define BOARD_SIZE 3
#define POSITION_FACTOR 20
#define DISTANCE_FACTOR 1
// Class
class Board
{
public:
	static Board* getInstance() { return &boardInstance; }
	irr::core::vector3df getCenterSlot();
	bool isEmptySlot(irr::core::vector3df position);
	void setSlot(irr::core::vector3df position, int player);
	int getSlot(int x, int y);
	bool checkWin();

private:
	static Board boardInstance;
	static int board[BOARD_SIZE][BOARD_SIZE];
	int getCoordinate(irr::f32 position);
};
