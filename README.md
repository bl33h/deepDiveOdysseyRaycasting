# deepDiveOdysseyRaycasting
The code represents a raycasting graphics application with a Finding Pirate's Treasure Under the Sea theme. It creates a 3D perspective effect by simulating rays of light and their interactions with a map.

<p align="center">
  <br>
  <img src="https://media.giphy.com/media/v1.Y2lkPTc5MGI3NjExOHpsd2RzZWZjanN6eGQ3dG1randuZWk0dW5rb3oyYmRydXF6djA2dSZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/cKLWT870ZJ9XwipnWw/giphy.gif" alt="pic" width="500">
  <br>
</p>

<p align="center">
  <a href="#Files">Files</a> •
  <a href="#Features">Features</a> •
  <a href="#how-to-use">How To Use</a>
</p>

## Files
- main.cpp: The main application file handling game logic, input, and rendering.
- raycaster.h: Header file containing the definition of the Raycaster class for handling raycasting.
- colors.h: Header file defining the Color struct for managing colors.
- constants.h: Header file with constant values used in the application.
- levels.h: Header file defining the Level struct and a vector of levels.
- resourceManager.h: Header file for the ResourceManager class responsible for loading and managing resources.
  
## Features
The main features of the graphics application include:

- Raycasting to create a 3D perspective effect.
- Loading and rendering levels from text files.
- Collision detection and handling.
- Menu system for level selection.
- Sound effects for player movement (bubbles) and victory (super mario bros win).

## How To Use

To clone and run this application, you'll need [WSL (Windows Subsystem for Linux)](https://learn.microsoft.com/en-us/windows/wsl/install) and the following tools installed on it: [Git](https://git-scm.com), [C++ compiler](https://www.fdi.ucm.es/profesor/luis/fp/devtools/mingw.html), [CMake](https://cmake.org/download/), [Make](https://linuxhint.com/install-make-ubuntu/), [glm](https://sourceforge.net/projects/glm.mirror/), [tbb](https://www.intel.com/content/www/us/en/developer/tools/oneapi/onetbb.html), and [SDL2](https://www.oreilly.com/library/view/rust-programming-by/9781788390637/386c15eb-41b2-41b4-bd65-154a750a58d8.xhtml). From your command line:

```bash
# Clone this repository
$ git clone https://github.com/bl33h/deepDiveOdysseyRaycasting

# Open the project
$ cd deepDiveOdysseyRaycasting

# Give execution permissions
$ chmod +x configure.sh
$ chmod +x build.sh
$ chmod +x run.sh

# Run the app
$ ./run.sh
