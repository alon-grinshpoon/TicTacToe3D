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
	bool win;
	// Check rows
	for (int i = 0; i < BOARD_SIZE; ++i) {
		win = true;
		for (int j = 0; j < BOARD_SIZE - 1; ++j) {
			if (board[i][j] != board[i][j + 1]
				|| board[i][j] == 0)
				win &= false;
		}
		if (win) return win;
	}
	// Check columns
	for (int j = 0; j < BOARD_SIZE; ++j) {
		win = true;
		for (int i = 0; i < BOARD_SIZE - 1; ++i) {
			if (board[i][j] != board[i + 1][j]
				|| board[i][j] == 0)
				win &= false;
		}
		if (win) return win;
	}
	// Check diagonals
	win = true;
	for (int i = 0; i < BOARD_SIZE - 1; ++i) {
		if (board[i][i] != board[i + 1][i + 1]
			|| board[i][i] == 0)
			win &= false;
	}
	if (win) return win;
	win = true;
	for (int i = 0; i < BOARD_SIZE - 1; ++i) {
		if (board[i][BOARD_SIZE - 1 - i] != board[i + 1][BOARD_SIZE - 2 - i]
			|| board[i][BOARD_SIZE - 1 - i] == 0)
			win &= false;
	}
	// Return win status
	return win;
}

int Board::getCoordinate(irr::f32 position)
{
	return (position + POSITION_FACTOR) / POSITION_FACTOR;
}
