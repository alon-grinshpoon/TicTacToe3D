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

vector3df Board::getEmptySlot()
{
	return vector3df(20, 20, 0);
}

void Board::setSlot(int row, int column, int player) {

}

bool Board::checkWin() {
	return false;
}
