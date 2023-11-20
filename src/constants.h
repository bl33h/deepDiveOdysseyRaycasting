/*---------------------------------------------------------------------------
Copyright (C), 2022-2023, Sara Echeverria (bl33h)
@author Sara Echeverria
FileName: constants.h
@version: I
Creation: 06/11/2023
Last modification: 17/11/2023
*Some parts were made using the AIs Bard and ChatGPT
------------------------------------------------------------------------------*/
#include "colors.h"
#include "raycaster.h"
#include "resourceManager.h"
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL_events.h>
#include <SDL_render.h>
#include <SDL2/SDL.h>
#include <SDL_video.h>

SDL_Window* window; // pointer to the SDL window
SDL_Renderer* renderer; // pointer to the SDL renderer
bool winnerConfig = false; // flag indicating if the game has a winner

Mix_Chunk* marineWalking = nullptr; // pointer to sound effect for marine walking
Mix_Chunk* winner = nullptr; // pointer to sound effect for winning
Mix_Chunk* turn = nullptr; // pointer to sound effect for turning