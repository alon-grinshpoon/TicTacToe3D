# TicTacToe3D
Apple recruitment challenge:  3D TicTacToe game implementation written in C++ using Irrlicht 1.8.4

## Project Structure

- __Code__: contains all source code, external libraries, and assets
  
  - __Assets__: Contains 3D models I created using Microsoft's 3D Builder and Autodesk Tinkercad.com, materials, and textures
  
  - __irrlicht-1.8.4__: A free open source C++ library that acts as a 3D engine and utilized OpenGL (http://irrlicht.sourceforge.net/)
  
  - __TicTacToe__: My Visual Studio solution containing all the source code
  
- __Research__: Links to preliminary research I did in order to develop a 3D app in C++

  - __3D Game Engines__: different C++ game engines I explored before choosing to use Irrlicht
  
  - __Cpp IDE__: A tutorial on how C++ development in Visual Studio
  
## App Structure
  
  - __AI.cpp/AI.h__: My simple AI implementation which randomly chooses a slot on the board. If it fails to randomly find a slot after a set number of attempts, it will scan the board from the bottom-left corner to find an empty slot.
  
  - __Board.cpp/Board.h__: The board implementation which holds the game's main data structure. The exact implementation is encapsulated in this cases, hidden from other game components.

  - __Keyboard.cpp/Keyboard.h__: An event handler customized to detect user input through the keyboard.

  - __TicTacToe.cpp/TicTacToe.h__: The game implementation which include a title screen and a game screen.
