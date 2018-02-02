// TicTacToe.cpp : Defines the entry point for the application.

// Includess
#include "stdafx.h"
#include "TicTacToe.h"
#include <stdio.h>  // Used for debugging
// Namespaces
using namespace irr; // Irrlicht namespace
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;
// Link with the Irrlicht.lib to use the Irrlicht.DLL file (already copied in the project folder)
#pragma comment(lib, PATH_LIB)

// Draw a frame
void drawFrame(IrrlichtDevice *window, IVideoDriver * driver, ISceneManager * smgr, IGUIEnvironment * guienv)
{
		driver->beginScene(true, true, COLOR_BACKGROUND);
		smgr->drawAll(); // Draw the 3D scene
		guienv->drawAll(); // Draw the GUI environment
		driver->endScene(); // End the scene
}

// Clear GUI
void clearGUI(ISceneManager * smgr, IGUIEnvironment * guienv)
{
	// Clear GUI enviroment
	guienv->clear();
	// Clear screen manager
	smgr->clear();
}

// Debug Prints
void debug(IGUIEnvironment * guienv, int player, Board* board, IAnimatedMeshSceneNode* node) {
	// Only print if DEBUG flag is activated in the header file
	if (DEBUG == 1) {
		// Debugging
		wchar_t m_string[256];

		swprintf_s(m_string, L"Player is %d", player);
		guienv->addStaticText(m_string, rect<s32>(10, 30, 260, 65), false);

		swprintf_s(m_string, L"%d %d %d",
			board->getSlot(0, 2), board->getSlot(1, 2), board->getSlot(2, 2)
		);
		guienv->addStaticText(m_string, rect<s32>(10, 50, 260, 85), false);
		swprintf_s(m_string, L"%d %d %d",
			board->getSlot(0, 1), board->getSlot(1, 1), board->getSlot(2, 1)
		);
		guienv->addStaticText(m_string, rect<s32>(10, 70, 260, 100), false);
		swprintf_s(m_string, L"%d %d %d",
			board->getSlot(0, 0), board->getSlot(1, 0), board->getSlot(2, 0)
		);
		guienv->addStaticText(m_string, rect<s32>(10, 90, 260, 120), false);

		swprintf_s(m_string, L"Location is %d %d", node->getPosition().X, node->getPosition().Y);
		guienv->addStaticText(m_string, rect<s32>(10, 110, 260, 140), false);
	}
}

// Title Screen
int titleScreen(IrrlichtDevice *window, IVideoDriver * driver, ISceneManager * smgr, IGUIEnvironment * guienv, Keyboard * keyboard) {

	// Add title mesh to window
	IAnimatedMesh* mesh = smgr->getMesh(PATH_ASSEST_TITLE);
	if (!mesh)
	{
		window->drop();
		return ERROR;
	}
	IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode(mesh, 0, 1, VECTOR_POSITION_TITLE);

	// Texture title mesh
	if (node)
	{
		node->setMaterialFlag(EMF_LIGHTING, false);
		node->setMD2Animation(scene::EMAT_STAND);
		node->setMaterialTexture(0, driver->getTexture(PATH_ASSEST_TEXTURE_OAK));
	}

	// Add static text to window showing instructions
	guienv->addStaticText(TEXT_INSTRUCTIONS_GENERAL,
		rect<s32>(175, 10, 660, 50), false);

	// Add camera
	smgr->addCameraSceneNode(0, VECTOR_POSITION_CAMERA, VECTOR_DIRECTION_CAMERA);
	// Other camera options
	//// smgr->addCameraSceneNodeMaya(0, -1500.0F, 200.0F, 1500.0F,-1,200.0F,true);
	//// smgr->addCameraSceneNodeFPS();

	// Intitialize a flag for quiting
	bool quit = false;

	// Run window
	while (window->run() && !quit)
	{
		if (!keyboard->IsPressed()) {

			// Start game
			if (keyboard->IsKeyDown(KEY_SPACE)) {
				// Release key
				keyboard->release(KEY_SPACE);
				// Unpress reciever
				keyboard->unpress();
				// Clear GUI
				clearGUI(smgr, guienv);
				// Start game
				break;
			}

			// Quit game
			if (keyboard->IsKeyDown(KEY_ESCAPE)) {
				quit = true;
				// Release key
				keyboard->release(KEY_ESCAPE);
			}

			// Unpress reciever
			keyboard->unpress();
		}

		// Draw frame
		drawFrame(window, driver, smgr, guienv);
	}

	return (quit == false) ? OK : QUIT;
}

// End Game
int endGame(bool pause, int turn, int player,  bool * restart, bool * quit, IAnimatedMesh** mesh, IAnimatedMeshSceneNode** node, IrrlichtDevice *window, IVideoDriver * driver, ISceneManager * smgr, IGUIEnvironment * guienv, Keyboard * keyboard) {
	if (!pause) {
		// Add title mesh to window
		if (turn > BOARD_SIZE * BOARD_SIZE) {
			*mesh = smgr->getMesh(PATH_ASSEST_TIE);
		}
		else if (player == PLAYER_AI) { // User (X) won, since AI is last
			*mesh = smgr->getMesh(PATH_ASSEST_WON);
		}
		else { // AI (O) won, since user is last
			*mesh = smgr->getMesh(PATH_ASSEST_LOST);
		}
		if (!mesh)
		{
			window->drop();
			return ERROR;
		}
		*node = smgr->addAnimatedMeshSceneNode(*mesh, 0, -1, VECTOR_POSITION_WON_OR_LOST);
		// Texture title mesh
		if (*node)
		{
			(*node)->setMaterialFlag(EMF_LIGHTING, false);
			(*node)->setMD2Animation(scene::EMAT_STAND);
			(*node)->setMaterialTexture(0, driver->getTexture(PATH_ASSEST_TEXTURE_OAK));
		}
		// Clear UI text
		guienv->clear();
		// Add static text to window showing instructions
		guienv->addStaticText(TEXT_INSTRUCTIONS_GENERAL,
			rect<s32>(315, 10, 660, 50), false);
		// Pause game
		pause = true;
	}

	// Check for keyboard interaction
	if (!keyboard->IsPressed()) {
		// Restart game
		if (keyboard->IsKeyDown(KEY_SPACE)) {
			*restart = true;
			// Release key
			keyboard->release(KEY_SPACE);
		}
		// Quit game
		if (keyboard->IsKeyDown(KEY_ESCAPE)) {
			*quit = true;
			// Release key
			keyboard->release(KEY_ESCAPE);
		}
		// Unpress reciever
		keyboard->unpress();
	}
}

// Initialzie Turn
int initalizeTurn(int player, IAnimatedMesh** mesh, IAnimatedMeshSceneNode** node, IrrlichtDevice *window, IVideoDriver * driver, ISceneManager * smgr, IGUIEnvironment * guienv, Keyboard * keyboard, Board * board) {
	// Clear GUI
	guienv->clear();
	// Set mesh
	
	if (player == PLAYER_USER) { // User's (X) turn
		*mesh = smgr->getMesh(PATH_ASSEST_X);
		// Add static text to window indicating it's the user's turn
		guienv->addStaticText(TEXT_TURN_USER,
			rect<s32>(10, 10, 260, 50), false);
		// Add static text to window showing game instructions
		guienv->addStaticText(TEXT_INSTRUCTIONS_GAME,
			rect<s32>(10, 30, 660, 50), false);
	}
	else { // AI's (O) turn
		*mesh = smgr->getMesh(PATH_ASSEST_O);
		// Add static text to window indicating it's the AI's turn
		guienv->addStaticText(TEXT_TURN_AI,
			rect<s32>(10, 10, 260, 50), false);
	}
	if (!mesh)
	{
		window->drop();
		return ERROR;
	}

	// Debug
	// debug(guienv, player, board, node);

	// Get center slot
	vector3df slot = board->getCenterSlot();
	// Skew distance from camera for visibily
	slot.Z -= DISTANCE_FACTOR;
	// Place X/O mesh
	*node = smgr->addAnimatedMeshSceneNode(*mesh, 0, -1, slot);
	// Texture X/O mesh
	if (node)
	{
		(*node)->setMaterialFlag(EMF_LIGHTING, false);
		(*node)->setMD2Animation(scene::EMAT_STAND);
		(*node)->setMaterialTexture(0, driver->getTexture(PATH_ASSEST_TEXTURE_WHITE));
	}
	return OK;
}

// User Gameplay
void playUser(int * player, bool * win, bool * turnStart, IAnimatedMeshSceneNode* node, Keyboard * keyboard, Board * board, IVideoDriver * driver) {
	
	vector3df nodePosition;

	// Check for keyboard interaction
	if (!keyboard->IsPressed()) {

		// Get position
		nodePosition = node->getPosition();

		// Update position (up/down and left/right)
		if (keyboard->IsKeyDown(KEY_KEY_W)) {
			// Move up if possible
			nodePosition.Y += (nodePosition.Y < POSITION_FACTOR) ? POSITION_FACTOR : 0;
			// Release key
			keyboard->release(KEY_KEY_W);
		}
		else if (keyboard->IsKeyDown(KEY_KEY_S)) {
			// Move down if possible
			nodePosition.Y -= (nodePosition.Y > -POSITION_FACTOR) ? POSITION_FACTOR : 0;
			// Release key
			keyboard->release(KEY_KEY_S);
		}
		if (keyboard->IsKeyDown(KEY_KEY_A)) {
			// Move left if possible
			nodePosition.X -= (nodePosition.X > -POSITION_FACTOR) ? POSITION_FACTOR : 0;
			// Release key
			keyboard->release(KEY_KEY_A);
		}
		else if (keyboard->IsKeyDown(KEY_KEY_D)) {
			// Move right if possible
			nodePosition.X += (nodePosition.X < POSITION_FACTOR) ? POSITION_FACTOR : 0;
			// Release key
			keyboard->release(KEY_KEY_D);
		}

		// Set position
		node->setPosition(nodePosition);

		// Set X/O
		if (keyboard->IsKeyDown(KEY_SPACE)) {
			// Check if slot empty
			if (board->isEmptySlot(node->getPosition())) {
				// Update board
				board->setSlot(node->getPosition(), *player);
				// Change texture
				node->setMaterialTexture(0, driver->getTexture(PATH_ASSEST_TEXTURE_OAK));
				// Skew back distance from camera
				vector3df nodePosition = node->getPosition();
				nodePosition.Z += DISTANCE_FACTOR;
				node->setPosition(nodePosition);
				// Check for win
				if (board->checkWin())
					*win = true;
				// Switch turn
				*player = (*player == PLAYER_USER) ? PLAYER_AI : PLAYER_USER;
				*turnStart = true;
			}
			// Release key
			keyboard->release(KEY_SPACE);
		}
	}
}

// AI Gameplay
void playAI(AI * ai, int * player, bool * win, bool * turnStart, IAnimatedMeshSceneNode* node, Board * board, IVideoDriver * driver) {
	
	vector3df nodePosition;

	// Get position
	nodePosition = ai->chooseSlot(*board);

	// Set position
	node->setPosition(nodePosition);

	// Set X/O
	board->setSlot(node->getPosition(), *player);
	// Change texture
	node->setMaterialTexture(0, driver->getTexture(PATH_ASSEST_TEXTURE_OAK));
	// Skew back distance from camera
	nodePosition = node->getPosition();
	nodePosition.Z += DISTANCE_FACTOR;
	node->setPosition(nodePosition);
	// Check for win
	if (board->checkWin())
		*win = true;
	// Switch turn
	*player = (*player == PLAYER_USER) ? PLAYER_AI : PLAYER_USER;
	*turnStart = true;
}

// Game Screen
int gameScreen(IrrlichtDevice *window, IVideoDriver * driver, ISceneManager * smgr, IGUIEnvironment * guienv, Keyboard * keyboard, Board * board, AI * ai) {
	
	// Start label
	start:

	// Add grid mesh to window
	IAnimatedMesh* mesh = smgr->getMesh(PATH_ASSEST_GRID);
	if (!mesh)
	{
		window->drop();
		return ERROR;
	}
	IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode(mesh);

	// Texture grid mesh
	if (node)
	{
		node->setMaterialFlag(EMF_LIGHTING, false);
		node->setMD2Animation(scene::EMAT_STAND);
		node->setMaterialTexture(0, driver->getTexture(PATH_ASSEST_TEXTURE_OAK));
	}

	// Add camera
	smgr->addCameraSceneNode(0, VECTOR_POSITION_CAMERA, VECTOR_DIRECTION_CAMERA);

	// Randomize first turn
	srand((unsigned)time(NULL));
	int player = rand() % 2 + 1; // 1 = User (X), 2 = AI (O)
	bool turnStart = true;
	int turn = 0;

	// Intitialize the flags for winning, quiting, pausing, and restarting
	bool win = false;
	bool pause = false;
	bool restart = false;
	bool quit = false;

	// Run window
	while (window->run() && !quit)
	{
		// Check if game needs to restart
		if (restart) {
			clearGUI(smgr, guienv);
			board->reset();
			goto start;
		} // Check if the game was won or a tie occured
		else if (win || turn > BOARD_SIZE * BOARD_SIZE) {
			// End the game
			int returnCode = endGame(pause, turn, player, &restart, &quit, &mesh, &node, window, driver, smgr, guienv, keyboard);
			if (returnCode == ERROR) return ERROR;
		}
		// Game is on
		else {
			// Add X/O mesh at the start of each turn
			if (turnStart) {
				// Increment turn
				++turn;
				// Initialize turn
				int returnCode = initalizeTurn(player, &mesh, &node, window, driver, smgr, guienv, keyboard, board);
				if (returnCode == ERROR) return ERROR;
				// Deactivate turn flag
				turnStart = false;
			}

			if (player == PLAYER_USER) { // User's (X) turn
				playUser(&player, &win, &turnStart, node, keyboard, board, driver);
			}
			else { // AI's (O) turn
				playAI(ai, &player, &win, &turnStart, node, board, driver);
			}

			// Quit game
			if (keyboard->IsKeyDown(KEY_ESCAPE)) {
				quit = true;
				// Release key
				keyboard->release(KEY_ESCAPE);
			}

			// Unpress reciever
			keyboard->unpress();
		}

		// Draw frame
		drawFrame(window, driver, smgr, guienv);
	}

	// Remove screen
	window->drop();

	// Return
	return OK;
}

// Main Function
int tictactoe() {

	// Initialize the board data structure
	Board* board = Board::getInstance();

	// Initialize the AI
	AI* ai = AI::getInstance();

	// Initialize the keyboard event receiver
	Keyboard * keyboard = Keyboard::getInstance();;

	// Create a game window
	IrrlichtDevice *window =
		createDevice(video::EDT_SOFTWARE, dimension2d<u32>(640, 480), 16,
			false, false, false, keyboard);

	// Check that window is successfully initialized
	if (!window) return 1;

	// Set window caption
	window->setWindowCaption(TEXT_WINDOW);

	// Get window components
	IVideoDriver* driver = window->getVideoDriver();
	ISceneManager* smgr = window->getSceneManager();
	IGUIEnvironment* guienv = window->getGUIEnvironment();

	// Set UI font
	guienv->getSkin()->setFont(guienv->getFont(PATH_FONT));

	// Start title screen
	int returnCode = titleScreen(window, driver, smgr, guienv, keyboard);
	if (returnCode == QUIT) {
		// Remove screen
		window->drop();
		// Return
		return OK;
	}

	// Start game screen, return its return code
	return gameScreen(window, driver, smgr, guienv, keyboard, board, ai);
}

// Application driver
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// Run Game
	return tictactoe();
}
