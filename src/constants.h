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

SDL_Window* window;
SDL_Renderer* renderer;
bool winnerConfig = false;

Mix_Chunk* marineWalking = nullptr;
Mix_Chunk* winner = nullptr;
Mix_Chunk* turn = nullptr;