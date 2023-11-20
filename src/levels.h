/*---------------------------------------------------------------------------
Copyright (C), 2022-2023, Sara Echeverria (bl33h)
@author Sara Echeverria
FileName: levels.h
@version: I
Creation: 06/11/2023
Last modification: 17/11/2023
*Some parts were made using the AIs Bard and ChatGPT
------------------------------------------------------------------------------*/
#include "colors.h"
#include "resourceManager.h"
#include "raycaster.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL_events.h>
#include <SDL_render.h>
#include <SDL_video.h>

// structure representing a game level
struct Level {
    std::string mapFile; // file path of the level map (src/assets/levels)
    std::string name; // name of the level
};

// vector containing predefined game levels
std::vector<Level> levels = {
    { "src/assets/levels/beginner.txt", "Beginner" },
    { "src/assets/levels/intermediate.txt", "Intermediate" },
    { "src/assets/levels/difficult.txt", "Difficult" },
};