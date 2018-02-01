// Includes
#include "stdafx.h"
#include "Board.h"
// Namespaces
using namespace irr; // Irrlicht namespace
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

Board Board::boardInstance;

int Board::board[BOARD_SIZE][BOARD_SIZE] = {
	{ 0,0,0 },
	{ 0,0,0 },
	{ 0,0,0 },
};

irr::core::vector3df Board::getCenterSlot()
{
	return vector3df(0, 0, 0);
}

bool Board::isEmptySlot(irr::core::vector3df position)
{
	// Calculate coordiantes
	int x = getCoordinate(position.X);
	int y = getCoordinate(position.Y);
	// Return if slot is empty
	return (board[x][y] == 0);
}

void Board::setSlot(irr::core::vector3df position, int player) {
	// Calculate coordiantes
	int x = getCoordinate(position.X);
	int y = getCoordinate(position.Y);
	// Update slot
	board[x][y] = player;
}

int Board::getSlot(int x, int y)
{
	return board[x][y];
}

bool Board::checkWin() {
	return false;
}

int Board::getCoordinate(irr::f32 position)
{
	return (position + POSITION_FACTOR) / POSITION_FACTOR;
}
