#pragma once
// Includes
#include "stdafx.h"
#include "Keyboard.h"
// Namespaces
using namespace irr; // Irrlicht namespace
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

// The keyboard single instance
Keyboard Keyboard::keyboardInstance;

// Store the current state of each key
bool KeyIsDown[KEY_KEY_CODES_COUNT];

// Flag for a single press
bool pressed;

bool Keyboard::OnEvent(const SEvent& event)
{
	// Remember whether each key is down or up
	if (event.EventType == irr::EET_KEY_INPUT_EVENT)
		if (!event.KeyInput.PressedDown)
			pressed = false;
		else
			KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
	return false;
}

// Check if a key was pressed
bool Keyboard::IsKeyDown(EKEY_CODE keyCode) const
{
return KeyIsDown[keyCode];
}

// Check if a key is released
bool Keyboard::IsKeyUp(EKEY_CODE keyCode) const
{
	return !KeyIsDown[keyCode];
}

// Check if a key is being held down
bool Keyboard::IsPressed() const
{
	return pressed;
}

// Set keyboard as unpressed
void Keyboard::unpress()
{
	pressed = false;
}

// Set a key as released
void Keyboard::release(EKEY_CODE keyCode)
{
	KeyIsDown[keyCode] = false;
}


