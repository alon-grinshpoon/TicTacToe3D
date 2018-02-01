#pragma once
// Includes
#include "stdafx.h"
#include "KeyboardEventReceiver.h"
// Namespaces
using namespace irr; // Irrlicht namespace
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

// Store the current state of each key
bool KeyIsDown[KEY_KEY_CODES_COUNT];

// Flag for a single press
bool pressed;

bool KeyboardEventReceiver::OnEvent(const SEvent& event)
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
bool KeyboardEventReceiver::IsKeyDown(EKEY_CODE keyCode) const
{
return KeyIsDown[keyCode];
}

// Check if a key is released
bool KeyboardEventReceiver::IsKeyUp(EKEY_CODE keyCode) const
{
	return !KeyIsDown[keyCode];
}

// Check if a key is being held down
bool KeyboardEventReceiver::IsPressed() const
{
	return pressed;
}

// Set keyboard as pressed
void KeyboardEventReceiver::press()
{
	pressed = true;
}

// Set a key as released
void KeyboardEventReceiver::release(EKEY_CODE keyCode)
{
	KeyIsDown[keyCode] = false;
}


