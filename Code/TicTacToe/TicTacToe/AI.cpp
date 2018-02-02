// Includes
#include "stdafx.h"
#include "AI.h"
// Namespaces
using namespace irr; // Irrlicht namespace
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

// The AI single instance
AI AI::aiInstance;

// Randomly choose an empty slot on the board
irr::core::vector3df AI::chooseSlot(Board board)
{
	int x = 0, y = 0;
	bool foundEmpty = false;
	// Try to find a empty slot randomly
	int attempt = 0;
	while (!foundEmpty && attempt++ < RANDOM_ATTEMPTS) {
		// Randomize slot
		x = rand() % BOARD_SIZE; // Random number between 0 and (BOARD_SIZE - 1)
		y = rand() % BOARD_SIZE; // Random number between 0 and (BOARD_SIZE - 1)
		// Check if empty
		if (board.isEmptySlot(x, y))
			foundEmpty = true;
	}
	// Random attemps failed, find one manually
	if (!foundEmpty) {
		for (int i = 0; i < BOARD_SIZE; ++i){
			for (int j = 0; j < BOARD_SIZE; ++j){
				if (board.isEmptySlot(i, j)) {
					x = i;
					y = j;
					foundEmpty = true;
					break;
				}
			}
			if (!foundEmpty) break;
		}
	}
	return vector3df(board.getPosition(x), board.getPosition(y), 0);
}
