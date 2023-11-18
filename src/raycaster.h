/*---------------------------------------------------------------------------
Copyright (C), 2022-2023, Sara Echeverria (bl33h)
@author Sara Echeverria
FileName: raycasting.h
@version: I
Creation: 06/11/2023
Last modification: 09/11/2023
*Some parts were made using the AIs Bard and ChatGPT
------------------------------------------------------------------------------*/

#include "colors.h"

constexpr size_t SCREEN_WIDTH = 800;
constexpr size_t SCREEN_HEIGHT= 600;

std::vector<Color> framebuffer(SCREEN_WIDTH * SCREEN_HEIGHT);

Color clearColor{0, 0, 0};
Color currentColor{255, 255, 255};

void clear() {
  std::vector<Color> framebuffer(SCREEN_WIDTH * SCREEN_HEIGHT);
  std::fill(framebuffer.begin(), framebuffer.end(), clearColor);
}