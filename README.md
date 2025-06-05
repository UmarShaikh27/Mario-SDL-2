# Mario SDL2 Game

A Mario-inspired side-scrolling platformer game built using SDL2 and C++.

## Game Features

- Classic Mario-style side-scrolling gameplay
- Coin collection system
- Obstacle avoidance
- Health system
- Background music and sound effects
- Continuous scrolling parallax background
- Score tracking system

## Controls

- **P** - Start the game
- **←** - Move left
- **→** - Move right
- **↑** - Jump
- **Q** - Quit game (after game over)
- **R** - Restart game (after game over)

## Prerequisites

To run this game, you need:

1. MinGW-w64 with g++ compiler
2. SDL2 development libraries:
   - SDL2
   - SDL2_image
   - SDL2_mixer

## Setup and Installation

1. Make sure you have MinGW-w64 installed and added to your system PATH
2. Download this folder (SDL2 library files in `lib/` and `include/` directories)
3. Ensure all SDL2 DLL files are in the same directory as the executable.

## Building and Running the Game

### Using Makefile (Recommended)

1. Open PowerShell in the project directory
2. Build the game:
```powershell
mingw32-make
```
3. Run the game:
```powershell
.\Game.exe
```

### Using Visual Studio Code

1. Open the project in Visual Studio Code
2. Use the built-in build task (Ctrl+Shift+B) or run:
```powershell
g++ *.cpp -I"./include/SDL2" -L"./lib" -w -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -o Game.exe
```
3. Run the generated `Game.exe`

### Using Command Line (Manual Compilation)

1. Open PowerShell in the project directory
2. Run the following command:
```powershell
g++ *.cpp -I"./include/SDL2" -L"./lib" -w -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -o Game.exe
```
3. Execute the game:
```powershell
.\Game.exe
```

## Game Structure

- `Game.cpp/hpp` - Main game logic and initialization
- `Mario.hpp` - Player character implementation
- `Obstacle.hpp/ObstacleGenerator.hpp` - Obstacle system
- `Coin.hpp/CoinGenerator.hpp` - Coin collection system
- `PlayerStates.hpp` - Player state management
- `Utility.hpp` - Utility functions for texture loading
- `Timer.hpp` - Game timing management

## Troubleshooting

If you encounter any issues:

1. Ensure all SDL2 DLLs are in the same directory as the executable
2. Verify that the `Images` and `Music` folders contain all required assets
3. Check that the SDL2 development libraries are properly installed and linked
4. Make sure you're using the correct version of MinGW-w64 (64-bit)
