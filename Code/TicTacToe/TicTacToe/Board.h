#pragma once
// Includes
#include <irrlicht.h> // Irrlicht h.file
#include <stdlib.h>
#include <time.h>	
// Static Variables
#define BOARD_SIZE 3
#define POSITION_FACTOR 20
#define DISTANCE_FACTOR 3
// Board Class
class Board
{
public:
	// Singleton Desgin 
	static Board* getInstance() { return &boardInstance; }
	// Get the center slot of the board
	irr::core::vector3df getCenterSlot();
	// Check if a given slot is empty
	bool isEmptySlot(irr::core::vector3df position);
	bool isEmptySlot(int x, int y);
	// Set X/O to a slot
	void setSlot(irr::core::vector3df position, int player);
	// Get the value on a slot on the board
	int getSlot(int x, int y);
	// Check if the board has a winning configuration
	bool checkWin();
	// Reset the board
	void reset();
	// Convert a board coordinate to a  3D position
	irr::f32 getPosition(int coordinate);
private:
	// The board instance
	static Board boardInstance;
	// The board data structure (a BOARD_SIZE * BOARD_SIZE matrix)
	static int board[BOARD_SIZE][BOARD_SIZE];
	// Convert a 3D position to a board coordinate
	int getCoordinate(irr::f32 position);
};
