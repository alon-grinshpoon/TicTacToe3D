// TicTacToe.cpp : Defines the entry point for the application.

// Includes
#include "stdafx.h"
#include "TicTacToe.h"
#include <irrlicht.h> // Irrlicht h.file
#include <stdlib.h>
#include <time.h>	
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
			KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

		return false;
	}

	// Check if a key is being held down
	virtual bool IsKeyDown(EKEY_CODE keyCode) const
	{
		return KeyIsDown[keyCode];
	}

	KeyboardEventReceiver()
	{
		for (u32 i = 0; i<KEY_KEY_CODES_COUNT; ++i)
			KeyIsDown[i] = false;
	}

private:
	// Store the current state of each key
	bool KeyIsDown[KEY_KEY_CODES_COUNT];
};

// TicTacToe Main Screen
int tictactoe() {
	
	// Initialize the board data structures
	#define BOARD_SIZE 3
	int board[BOARD_SIZE][BOARD_SIZE] =
	{
		{ 0,0,0 },
		{ 0,0,0 },
		{ 0,0,0 }
	};
	IAnimatedMesh* x[BOARD_SIZE * BOARD_SIZE];
	IAnimatedMesh* o[BOARD_SIZE * BOARD_SIZE];

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

	// Add static text to window
	guienv->addStaticText(L"It's the player's turn!",
		rect<s32>(10, 10, 260, 22), false);

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

	// Frame rate timer
	u32 timer = window->getTimer()->getTime();

	// Speed in units per second
	const f32 SPEED = 5.f;
	
	// Randomize turn
	srand(time(NULL));
	int isPlayersTurn = rand() % 2 + 1; // 1 = Player (X), 2 = AI (O)
	bool turnStart = true;

	// Run window
	while (window->run())
	{
		// Add X/O mesh in an empty slot at the start of each turn
		if (turnStart) {
			if (isPlayersTurn == 1) // Player's (X) turn
				mesh = smgr->getMesh("../../Resources/X.obj");
			else // AI's (O) turn
				mesh = smgr->getMesh("../../Resources/O.obj");
			if (!mesh)
			{
				window->drop();
				return 1;
			}
			// Choose empty slot

			// Place X/O mesh
			node = smgr->addAnimatedMeshSceneNode(mesh, 0, -1, vector3df(20, 20, 0));
			// Texture X/O mesh
			if (node)
			{
				node->setMaterialFlag(EMF_LIGHTING, false);
				node->setMD2Animation(scene::EMAT_STAND);
				node->setMaterialTexture(0, driver->getTexture("../../Resources/white.jpg"));
			}
			turnStart = false;
		}

		// Calculate the frame delta time
		const u32 now = window->getTimer()->getTime();
		const f32 frameDeltaTime = (f32)(now - timer) / 1000.f; // Time in seconds
		timer = now;

		// Check for keyboard interaction
		core::vector3df nodePosition = node->getPosition();
		if (receiver.IsKeyDown(irr::KEY_KEY_W))
			nodePosition.Y += SPEED * frameDeltaTime;
		else if (receiver.IsKeyDown(irr::KEY_KEY_S))
			nodePosition.Y -= SPEED * frameDeltaTime;

		if (receiver.IsKeyDown(irr::KEY_KEY_A))
			nodePosition.X -= SPEED * frameDeltaTime;
		else if (receiver.IsKeyDown(irr::KEY_KEY_D))
			nodePosition.X += SPEED * frameDeltaTime;
		node->setPosition(nodePosition);

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
