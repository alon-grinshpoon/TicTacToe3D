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
#pragma comment(lib, "../../irrlicht-1.8.4/lib/Win32-visualstudio/Irrlicht.lib")
// Static Variables
# define DEBUG 1 // Debugging flag
#define MAX_LOADSTRING 100
// Global Variables
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
												// Forward declarations of functions
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// Keyboard Event Receiver
class KeyboardEventReceiver : public IEventReceiver
{
public:

	virtual bool OnEvent(const SEvent& event)
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
	virtual bool IsKeyDown(EKEY_CODE keyCode) const
	{
		return KeyIsDown[keyCode];
	}

	// Check if a key is released
	virtual bool IsKeyUp(EKEY_CODE keyCode) const
	{
		return !KeyIsDown[keyCode];
	}

	// Check if a key is being held down
	virtual bool IsPressed() const
	{
		return pressed;
	}

	// Set keyboard as pressed
	virtual void press()
	{
		pressed = true;
	}

	// Set a key as released
	virtual void release(EKEY_CODE keyCode)
	{
		KeyIsDown[keyCode] = false;
	}

	// Constructor
	KeyboardEventReceiver()
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

// TicTacToe Main Screen
int tictactoe() {

	// Initialize the board data structure
	Board* board = Board::getInstance();

	// Create a keyboard event receiver
	KeyboardEventReceiver receiver;

	// Create a game window
	IrrlichtDevice *window =
		createDevice(video::EDT_SOFTWARE, dimension2d<u32>(640, 480), 16,
			false, false, false, &receiver);

	// Check that window is successfully initialized
	if (!window) return 1;

	// Set window caption
	window->setWindowCaption(L"TicTacToe - Alon Grinshpoon's Apple Challenge");

	// Get window components
	IVideoDriver* driver = window->getVideoDriver();
	ISceneManager* smgr = window->getSceneManager();
	IGUIEnvironment* guienv = window->getGUIEnvironment();

	// Start label
	start:

	// Add grid mesh to window
	IAnimatedMesh* mesh = smgr->getMesh("../../Resources/grid.obj");
	if (!mesh)
	{
		window->drop();
		return 1;
	}
	IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode(mesh);
	// Texture grid mesh
	if (node)
	{
		node->setMaterialFlag(EMF_LIGHTING, false);
		node->setMD2Animation(scene::EMAT_STAND);
		node->setMaterialTexture(0, driver->getTexture("../../Resources/oak.jpg"));
	}

	// Add camera
	smgr->addCameraSceneNode(0, vector3df(0, 0, -80), vector3df(0, 0, 0));
	// smgr->addCameraSceneNodeMaya(0, -1500.0F, 200.0F, 1500.0F,-1,200.0F,true);
	// smgr->addCameraSceneNodeFPS();

	// Randomize turn
	srand(time(NULL));
	int player = rand() % 2 + 1; // 1 = User (X), 2 = AI (O)
	bool turnStart = true;
	int turn = 0;

	// Intitialize a flags for winning, quiting, pausing, and restarting
	bool win = false;
	bool quit = false;
	bool pause = false;
	bool restart = false;

	// Run window
	while (window->run() && !quit)
	{
		// Check if game was won 
		if (restart) {
			guienv->clear();
			smgr->clear();
			board->reset();
			goto start;
		}
		else if (win) {
			if (!pause) {
				// Add winning title meesh to window
				if (player == 2) { // User (X) won, since AI is last
					mesh = smgr->getMesh("../../Resources/won.obj");
				}
				else { // AI (O) won, since user is last
					mesh = smgr->getMesh("../../Resources/lost.obj");
				}
				if (!mesh)
				{
					window->drop();
					return 1;
				}
				node = smgr->addAnimatedMeshSceneNode(mesh, 0, -1, vector3df(0,0,-30));
				// Texture grid mesh
				if (node)
				{
					node->setMaterialFlag(EMF_LIGHTING, false);
					node->setMD2Animation(scene::EMAT_STAND);
					node->setMaterialTexture(0, driver->getTexture("../../Resources/oak.jpg"));
				}
				// Pause game
				pause = true;
			}

			// Check for keyboard interaction
			if (!receiver.IsPressed()) {
				// Restart game
				if (receiver.IsKeyDown(KEY_SPACE)) {
					restart = true;
					// Release key
					receiver.release(KEY_SPACE);
				}
				// Quit game
				if (receiver.IsKeyDown(KEY_ESCAPE)) {
					quit = true;
					// Release key
					receiver.release(KEY_ESCAPE);
				}
				// Unpress reciever
				receiver.press();
			}
		}
		// Check if a tie occured
		else if (turn > BOARD_SIZE * BOARD_SIZE) {

		}
		// Game is on
		else {
			// Add X/O mesh in an empty slot at the start of each turn
			if (turnStart) {
				// Increment turn
				++turn;
				// Clear GUI
				guienv->clear();
				// Set mesh
				if (player == 1) { // User's (X) turn
					mesh = smgr->getMesh("../../Resources/X.obj");
					// Add static text to window
					guienv->addStaticText(L"It's your turn!",
						rect<s32>(10, 10, 260, 22), false);
				}
				else { // AI's (O) turn
					mesh = smgr->getMesh("../../Resources/O.obj");
					// Add static text to window
					guienv->addStaticText(L"It's the AI's turn!",
						rect<s32>(10, 10, 260, 22), false);
				}
				if (!mesh)
				{
					window->drop();
					return 1;
				}

				if (DEBUG == 1){
					// Debugging
					wchar_t m_string[256];

					swprintf_s(m_string, L"Player is %d", player);
					guienv->addStaticText(m_string,	rect<s32>(10, 20, 260, 30), false);

					swprintf_s(m_string, L"%d %d %d",
						board->getSlot(0, 2), board->getSlot(1, 2), board->getSlot(2, 2)
					);
					guienv->addStaticText(m_string, rect<s32>(10, 30, 260, 60), false);
					swprintf_s(m_string, L"%d %d %d",
						board->getSlot(0, 1), board->getSlot(1, 1), board->getSlot(2, 1)
					);
					guienv->addStaticText(m_string, rect<s32>(10, 40, 260, 60), false);
					swprintf_s(m_string, L"%d %d %d",
						board->getSlot(0, 0), board->getSlot(1, 0), board->getSlot(2, 0)
					);
					guienv->addStaticText(m_string, rect<s32>(10, 50, 260, 60), false);
					swprintf_s(m_string, L"Location is %d %d", node->getPosition().X, node->getPosition().Y);
					guienv->addStaticText(m_string, rect<s32>(10, 60, 260, 80), false);
				}

				// Get center slot
				vector3df slot = board->getCenterSlot();
				// Skew distance from camera for visibily
				slot.Z -= DISTANCE_FACTOR;
				// Place X/O mesh
				node = smgr->addAnimatedMeshSceneNode(mesh, 0, -1, slot);
				// Texture X/O mesh
				if (node)
				{
					node->setMaterialFlag(EMF_LIGHTING, false);
					node->setMD2Animation(scene::EMAT_STAND);
					node->setMaterialTexture(0, driver->getTexture("../../Resources/white.jpg"));
				}
				turnStart = false;
			}

			// Check for keyboard interaction
			if (!receiver.IsPressed()) {

				// Get position
				vector3df nodePosition = node->getPosition();

				// Update position (up/down and left/right)
				if (receiver.IsKeyDown(KEY_KEY_W)) {
					// Move up if possible
					nodePosition.Y += (nodePosition.Y < POSITION_FACTOR) ? POSITION_FACTOR : 0;
					// Release key
					receiver.release(KEY_KEY_W);
				}
				else if (receiver.IsKeyDown(KEY_KEY_S)) {
					// Move down if possible
					nodePosition.Y -= (nodePosition.Y > -POSITION_FACTOR) ? POSITION_FACTOR : 0;
					// Release key
					receiver.release(KEY_KEY_S);
				}
				if (receiver.IsKeyDown(KEY_KEY_A)) {
					// Move left if possible
					nodePosition.X -= (nodePosition.X > -POSITION_FACTOR) ? POSITION_FACTOR : 0;
					// Release key
					receiver.release(KEY_KEY_A);
				}
				else if (receiver.IsKeyDown(KEY_KEY_D)) {
					// Move right if possible
					nodePosition.X += (nodePosition.X < POSITION_FACTOR) ? POSITION_FACTOR : 0;
					// Release key
					receiver.release(KEY_KEY_D);
				}

				// Set position
 				node->setPosition(nodePosition);

				// Set X/O
				if (receiver.IsKeyDown(KEY_SPACE)) {
					// Check if slot empty
					if (board->isEmptySlot(node->getPosition())){
						// Update board
						board->setSlot(node->getPosition(), player);
						// Change texture
						node->setMaterialTexture(0, driver->getTexture("../../Resources/oak.jpg"));
						// Skew back distance from camera
						vector3df nodePosition = node->getPosition();
						nodePosition.Z += DISTANCE_FACTOR;
						node->setPosition(nodePosition);
						// Check for win
						if (board->checkWin())
							win = true;
						// Switch turn
						player = (player == 1) ? 2 : 1;
						turnStart = true;
					}
					// Release key
					receiver.release(KEY_SPACE);
				}

				// Quit game
				if (receiver.IsKeyDown(KEY_ESCAPE)) {
					quit = true;
					// Release key
					receiver.release(KEY_ESCAPE);
				}

				// Unpress reciever
				receiver.press();
			}
		}

		// Draw frame
		driver->beginScene(true, true, SColor(255, 50, 95, 170));
		smgr->drawAll(); // Draw the 3D scene
		guienv->drawAll(); // Draw the GUI environment
		driver->endScene(); // End the scene
	}

	// Remove screen
	window->drop();

	// Return
	return 0;
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

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TICTACTOE));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_TICTACTOE);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code that uses hdc here...
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
