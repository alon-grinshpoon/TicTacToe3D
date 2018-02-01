#pragma once
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

// Keyboard Event Receiver
class KeyboardEventReceiver : public IEventReceiver
{
public:
	// On even handler
	virtual bool OnEvent(const SEvent& event);
	// Check if a key was pressed
	virtual bool IsKeyDown(EKEY_CODE keyCode) const;
	// Check if a key is released
	virtual bool IsKeyUp(EKEY_CODE keyCode) const;
	// Check if a key is being held down
	virtual bool IsPressed() const;
	// Set keyboard as pressed
	virtual void press();
	// Set a key as released
	virtual void release(EKEY_CODE keyCode);
	// Constructor
	KeyboardEventReceiver::KeyboardEventReceiver()
	{
		for (u32 i = 0; i < KEY_KEY_CODES_COUNT; ++i)
			KeyIsDown[i] = false;
		pressed = false;
	}

private:
	// Store the current state of each key
	bool KeyIsDown[KEY_KEY_CODES_COUNT];
	// Flag for a single press
	bool pressed;
};

