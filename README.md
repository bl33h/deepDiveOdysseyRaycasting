# deepDiveOdysseyRaycasting

The code represents a program for

<p align="center">
  <br>
  <img src="" alt="pic" width="500">
  <br>
</p>

<p align="center">
  <a href="#Files">Files</a> •
  <a href="#Features">Features</a> •
  <a href="#how-to-use">How To Use</a>
</p>

## Files

- **configure.sh**: A shell script to set up the project dependencies and environment.
- **build.sh**: A shell script to build the project using CMake.
- **run.sh**: A shell script to execute the compiled graphics application.
- **clean.sh**: A shell script to clean up build artifacts and generated files.
- **src**: A directory containing the source code files for the graphics application.
  - **barycentric.cpp**: Implementation of functions related to barycentric coordinates calculation.
  - **border.cpp**: Implementation of functions for drawing lines.
  - **border.h**: Header file declaring functions for drawing lines.
  - **colors.h**: Header file defining color structures and operations.
  - **fragment.h**: Header file defining fragment and shader-related structures.
  - **framebuffer.cpp**: Implementation of functions for handling the frame buffer.
  - **framebuffer.h**: Header file declaring functions and data structures for managing the frame buffer.
  - **print.h**: Header file containing functions for printing various data types.
  - **shaders.h**: Header file defining fragment and vertex shader functions.
  - **trianglefill.cpp**: Implementation of functions for loading 3D models.
  - **trianglefill.h**: Header file declaring functions and data structures for loading 3D models.
  - **triangles.h**: Header file declaring functions and structures related to triangle rendering.

## Features

The main features of the graphics application include:

- Loading and rendering 3D models.
- Flat shading of the 3D models.
- Use of barycentric coordinates for triangle rendering.

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
