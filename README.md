# TicTacToe3D
Apple Recruitment Challenge: 3D/AI TicTacToe game implementation written in C++ using Irrlicht 1.8.4 (for OpenGL)

Developed by Alon Grinshpoon (alon.grinshpoon@gmail.com) on January 2018.

Demo video on YouTube (unlisted): https://youtu.be/acUKPvx-JCk

## Project Structure

- __Code__: contains all source code, external libraries, and assets
  
  - __Assets__: Contains 3D models I created using Microsoft's 3D Builder and Autodesk Tinkercad.com, materials, and textures
  
  - __irrlicht-1.8.4__: A free open source C++ library that acts as a 3D engine and utilized OpenGL (http://irrlicht.sourceforge.net/)
  
  - __TicTacToe__: My Visual Studio solution containing all the source code
 
- __Demo Video__: Contains a demo video demonstrating a game with multiple rounds between a user and the game's AI (Includes all scenarios of win, lose, tie). Also unlisted on YouTube under https://youtu.be/acUKPvx-JCk
 
- __Research__: Links to preliminary research I did in order to develop a 3D app in C++

  - __3D Game Engines__: different C++ game engines I explored before choosing to use Irrlicht
  
  - __Cpp IDE__: A tutorial on how C++ development in Visual Studio
  
## App Structure
  
  - __AI.cpp/AI.h__: My simple AI implementation which randomly chooses a slot on the board. If it fails to randomly find a slot after a set number of attempts, it will scan the board from the bottom-left corner to find an empty slot.
  
  - __Board.cpp/Board.h__: The board implementation which holds the game's main data structure. The exact implementation is encapsulated in this cases, hidden from other game components.

  - __Keyboard.cpp/Keyboard.h__: An event handler customized to detect user input through the keyboard.

  - __TicTacToe.cpp/TicTacToe.h__: The game implementation which include a title screen and a game screen.

## Installation Guide

1. Clone the reop.
2. Double-click ~/TicTacToe3D/Code/TicTacToe/TicTacToe.sln
3. Visual Studio 2017 should open the project automatically.
4. On the top bar, make sure x86 is set before running.
5. Run.

## Troubleshooting

In the case of compiler errors:

1. Right-click on the _TickTakToe_ project (not the entire Solution!) in the Solution Explorer.
2. Choose _Properties_.
3. On the left menu, under _Configuration Properties_, select _VC++ Directories_.
4. For the configuration your are trying to run (Debug, Release, etc) make sure that __..\..\irrlicht-1.8.4\include__ is found under _Include Directories_, and __..\..\irrlicht-1.8.4\lib\Win32-visualstudio;__ is found under _Library Directories_.
