# Queendom Chronicles: Simulation Game

Welcome to **Queendom Chronicles**, a simulation game built using C++ and the Doodle graphics library. In this game, players can manage resources, build a thriving town, and interact with NPCs. You can earn money, buy houses, and strategically place buildings to expand your Queendom.

## Features
- **Resource Management**: Collect wood, stone, and food to build and maintain structures.
- **Building System**: Choose from a variety of buildings such as production facilities, houses, and decorations.
- **NPC Interaction**: NPCs roam the map and can interact with the player.
- **Shop and Economy**: Use the in-game shop to purchase and upgrade buildings or save up to buy new houses.
- **Camera System**: Move the camera to explore your expanding Queendom using the W, A, S, D keys.

---

## Getting Started

### Prerequisites
To run the game, you will need:
- A working installation of Visual Studio (with support for C++ development)
- Doodle Graphics Library
- Windows operating system (due to Windows-specific headers and functionality)

### Setting Up the Project
1. **Clone or Download the Repository**: Ensure you have all the files, including `main.cpp`, the assets folder, and necessary headers.
2. **Open the Solution File**: Open the `.sln` file using Visual Studio. This will load the entire project setup.
3. **Set Up Dependencies**:
   - Ensure that the Doodle graphics library is correctly linked in the project settings.
   - Make sure all asset paths are set properly.

### How to Run
1. **Build the Project**: Click on `Build` from the Visual Studio toolbar and select `Build Solution`. Ensure there are no compilation errors.
2. **Run the Game**: Click on the green `Start` button or press `F5` to run the game in Debug mode.
   - In the final release version, the console window will be hidden for a cleaner experience.

---

## Controls
- **Camera Movement**: Use `W`, `A`, `S`, `D` keys to move the camera around the map.
- **Interacting with Buttons**: Click on the "Play Game" and "Credits" buttons in the main menu to start playing or view credits.

## Game Structure
The game has a modular architecture:
- **Main Menu**: Displays options to play the game or view credits.
- **Game Manager**: Handles resource allocation, building management, and NPC updates.
- **Buildings**: Players can build and upgrade different types of structures like lumber camps, quarries, and houses.
- **Camera**: Provides smooth navigation across the game world, ensuring players can easily view and manage their Queendom.

---

## How to Add or Modify Content
1. **Adding New Buildings**: Add new building types in `GameManager::Setup()` and ensure proper images and attributes are linked.
2. **Creating NPCs**: NPCs can be added in the `GameManager::Setup()` by specifying their positions and names.
3. **Customizing the Game**: Modify constants such as `window_width` and `window_height` in `Window.h` to adjust the game resolution.

---

## Troubleshooting
- **Missing Assets**: Ensure all images and assets are located in the `Assets` folder and that paths are correctly specified.
- **Compilation Errors**: Double-check the Doodle library configuration and include paths in Visual Studio.

---

Enjoy building and managing your Queendom! Happy gaming!
