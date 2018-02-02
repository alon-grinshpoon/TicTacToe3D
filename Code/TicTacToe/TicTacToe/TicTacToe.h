#pragma once
// Includes
#include "resource.h"
#include "Board.h"
#include "AI.h"
#include "Keyboard.h"
#include <stdlib.h>
#include <time.h>
// Static Variables

# define DEBUG						0 // Debugging flag
# define ERROR						1 // Debugging flag
# define OK							0 // Debugging flag
# define QUIT						2 // Debugging flag

# define PLAYER_AI					2
# define PLAYER_USER				1

#define PATH_LIB					"../../irrlicht-1.8.4/lib/Win32-visualstudio/Irrlicht.lib"
#define PATH_FONT					"../../irrlicht-1.8.4/media/font_dejavu_sans.png"

#define PATH_ASSEST_TITLE			"../../Assets/title.obj"
#define PATH_ASSEST_TEXTURE_OAK		"../../Assets/oak.jpg"
#define PATH_ASSEST_TEXTURE_WHITE	"../../Assets/white.jpg"
#define PATH_ASSEST_GRID			"../../Assets/grid.obj"
#define PATH_ASSEST_TIE				"../../Assets/tie.obj"
#define PATH_ASSEST_WON				"../../Assets/won.obj"
#define PATH_ASSEST_LOST			"../../Assets/lost.obj"
#define PATH_ASSEST_X				"../../Assets/X.obj"
#define PATH_ASSEST_O				"../../Assets/O.obj"

#define TEXT_WINDOW					L"TicTacToe - Alon Grinshpoon's Apple Challenge"
#define TEXT_INSTRUCTIONS_GENERAL	L"Press SPACE to start or ESC to quit."
#define TEXT_INSTRUCTIONS_GAME		L"Use W S A D to move shape and SPACE to set it."

#define TEXT_TURN_USER				L"It's your turn!"
#define TEXT_TURN_AI				L"It's the AI's turn!"

#define COLOR_BACKGROUND			SColor(255, 70, 180, 90)

#define VECTOR_POSITION_TITLE		vector3df(0, -2.0f, 0)
#define VECTOR_POSITION_CAMERA		vector3df(0, 0, -80)
#define VECTOR_POSITION_WON_OR_LOST	vector3df(0, 0, -30)
#define VECTOR_DIRECTION_CAMERA		vector3df(0, 0, 0)


/* Functions Decleration */
// Draw frame
static void drawFrame(IrrlichtDevice *window, IVideoDriver* driver, ISceneManager* smgr, IGUIEnvironment* guienv);
// Clear GUI
static void clearGUI(ISceneManager* smgr, IGUIEnvironment* guienv);
// Debug Prints
void debug(IGUIEnvironment * guienv, int player, Board* board, IAnimatedMeshSceneNode* node);
// Title Screen
int titleScreen(IrrlichtDevice *window, IVideoDriver * driver, ISceneManager * smgr, IGUIEnvironment * guienv, Keyboard * keyboard);
// Game Screen
int gameScreen(IrrlichtDevice *window, IVideoDriver * driver, ISceneManager * smgr, IGUIEnvironment * guienv, Keyboard * keyboard, Board * board, AI * ai);
// Main Function
int tictactoe();
// Initialzie Turn
int initalizeTurn(int player, IAnimatedMesh** mesh, IAnimatedMeshSceneNode** node, IrrlichtDevice *window, IVideoDriver * driver, ISceneManager * smgr, IGUIEnvironment * guienv, Keyboard * keyboard, Board * board);
// User Gameplay
void playUser(int * player, bool * win, bool * turnStart, IAnimatedMeshSceneNode* node, Keyboard * keyboard, Board * board, IVideoDriver * driver);
// AI Gameplay
void playAI(AI * ai, int * player, bool * win, bool * turnStart, IAnimatedMeshSceneNode* node, Board * board, IVideoDriver * driver);