#pragma once
// Includes
#include <irrlicht.h> // Irrlicht h.file
#include <stdlib.h>
#include <time.h>
#include "Board.h"
// Static Variables
#define RANDOM_ATTEMPTS 15
// AI Class
class AI
{
public:
	// Singleton Desgin 
	static AI* getInstance() { return &aiInstance; }
	// Randomly choose an empty slot on the board
	irr::core::vector3df chooseSlot(Board board);
private:
	// The AI instance
	static AI aiInstance;
};
