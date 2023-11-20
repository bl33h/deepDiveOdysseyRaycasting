/*---------------------------------------------------------------------------
Copyright (C), 2022-2023, Sara Echeverria (bl33h)
@author Sara Echeverria
FileName: raycaster.h
@version: I
Creation: 06/11/2023
Last modification: 17/11/2023
*Some parts were made using the AIs Bard and ChatGPT
------------------------------------------------------------------------------*/
#pragma once
#include <iostream>
#include <fstream>
#include <SDL_render.h>
#include <string>
#include <vector>
#include <cmath>
#include <SDL2/SDL.h>
#include <unordered_map>
#include "colors.h"
#include "resourceManager.h"
#include <array>

const Color B = {245, 236, 255}; // background color
const Color W = {255, 255, 255}; // clear color
const int WIDTH = 16; // width of the game map
const int HEIGHT = 11; // height of the game map
const int BLOCK = 50; // size of a map block
const int SCREEN_WIDTH = WIDTH * BLOCK; // screen width
const int SCREEN_HEIGHT = HEIGHT * BLOCK; // Screen height
int minimapWidth = SCREEN_WIDTH / 4; // width of the minimap
int minimapHeight = SCREEN_HEIGHT / 4; // height of the minimap
int minimapX = SCREEN_WIDTH - minimapWidth; // x-coordinate of the minimap
int minimapY = 0; // y-coordinate of the minimap
float minimapScale = 0.25f; // scale factor for the minimap

// structure representing a 2D point
struct Point {
  int x; // x-coordinate
  int y; // y-coordinate
};

// structure representing a player in the game
struct Player {
  int x;
  int y;
  float a;
  float fov;
}; 

// structure representing the impact information of a ray *avoids coll
struct Impact {
  float d;
  std::string mapHit;
  int tx;
};

// class for raycasting and rendering the game
class Raycaster {
public:
  Raycaster(SDL_Renderer* renderer)
    : renderer(renderer) {

    player.x = BLOCK + BLOCK / 2;
    player.y = BLOCK + BLOCK / 2;

    player.a = M_PI / 4.0f;
    player.fov = M_PI / 3.0f;

    scale = 50;
    tsize = 128;
  }

  // draws a point on the renderer with the given color
  void point(int x, int y, Color c) {
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
    SDL_RenderDrawPoint(renderer, x, y);
  }

  // loads the game map from a file
  bool loadMap(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    while (getline(file, line)) {
      map.push_back(line);
    }
    file.close();
    return true;
  }

  // draws a rectangle on the renderer with a specified texture map
  void rect(int x, int y, const std::string& mapHit, int width, int height) {
    float minimapScale = 10.0f;
    int scaledWidth = static_cast<int>(width);
    int scaledHeight = static_cast<int>(height);

    for (int cx = x; cx < x + scaledWidth; cx++) {
        for (int cy = y; cy < y + scaledHeight; cy++) {
            int tx = static_cast<int>((cx - x) / minimapScale);
            int ty = static_cast<int>((cy - y) / minimapScale);

            if (tx >= 0 && tx < tsize && ty >= 0 && ty < tsize) {
                Color c = ResourceManager::getPixelColor(mapHit, tx, ty);
                SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, 255);
                SDL_RenderDrawPoint(renderer, cx, cy);
            }
        }
    }
}

  // casts a ray and returns impact information
  Impact castR(float a) {
    float d = 0;
    std::string mapHit;
    int tx;

    while(true) {
      int x = static_cast<int>(player.x + d * cos(a)); 
      int y = static_cast<int>(player.y + d * sin(a)); 
      
      int i = static_cast<int>(x / BLOCK);
      int j = static_cast<int>(y / BLOCK);


      if (map[j][i] != ' ') {
        mapHit = map[j][i];

        int hitx = x - i * BLOCK;
        int hity = y - j * BLOCK;
        int maxhit;

        if (hitx == 0 || hitx == BLOCK - 1) {
          maxhit = hity;
        } else {
          maxhit = hitx;
        }

        tx = maxhit * tsize / BLOCK;

        break;
      }
     
      point((x * minimapScale) + minimapX, (y * minimapScale) + minimapY, W);
      
      d += 1;
    }
    return Impact{d, mapHit, tx};
  }

  // draws a stake on the renderer
  void drawStake(int x, float h, Impact i) {
    float start = SCREEN_HEIGHT/2.0f - h/2.0f;
    float end = start + h;

    for (int y = start; y < end; y++) {
      int ty = (y - start) * tsize / h;
      Color c = ResourceManager::getPixelColor(i.mapHit, i.tx, ty);
      SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);

      SDL_RenderDrawPoint(renderer, x, y);
    }
  }

  // checks if the player is on the winning position (found the treasure)
  bool checkWinner() {
    std::array<Point, 4> Offset = {Point{-1,0},Point{0,1}, Point{1,0}, Point{0,-1} };
    for (int i = 0; i < 4; i++ ){
      int playerX = static_cast<int>(player.x / BLOCK) + Offset[i].x;
      int playerY = static_cast<int>(player.y / BLOCK) + Offset[i].y;

      if (playerX >= 0 && playerX < WIDTH && playerY >= 0 && playerY < HEIGHT) {
        char mapChar = map[playerY][playerX];
        if (mapChar == 'g') {
          return true;
        }
      }
    }
      return false;
    }

  // checks for coll at a given position
  bool checkCollision(int x, int y) {
      int i = x / BLOCK;
      int j = y / BLOCK;
      return map[j][i] != ' ';
  }

  // renders the game scene
  void render() {

    for (int i = 0; i < SCREEN_WIDTH; i++) {
      double a = player.a + player.fov / 2.0 - player.fov * i / SCREEN_WIDTH;
      Impact impact = castR(a);
      float d = impact.d;
      Color c = Color(255, 0, 0);
      int x = i;
      float h = static_cast<float>(SCREEN_HEIGHT)/static_cast<float>(d) * static_cast<float>(scale);
      drawStake(x, h, impact);
    }

    SDL_SetRenderDrawColor(renderer, 79, 66, 95, 255);  
    SDL_Rect minimapRect = {minimapX, minimapY, minimapWidth, minimapHeight};
    SDL_RenderFillRect(renderer, &minimapRect);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); 
    SDL_Rect minimapBorder = {minimapX - 2, minimapY - 2, minimapWidth + 4, minimapHeight + 4};
    SDL_RenderDrawRect(renderer, &minimapBorder);

    for (int x = 0; x < SCREEN_WIDTH; x += BLOCK) {
        for (int y = 0; y < SCREEN_HEIGHT; y += BLOCK) {
            int i = static_cast<int>(x / BLOCK);
            int j = static_cast<int>(y / BLOCK);

            if (map[j][i] != ' ') {
                int minimapXCoord = minimapX + static_cast<int>(x * minimapScale);
                int minimapYCoord = minimapY + static_cast<int>(y * minimapScale);
                int minimapBlock = static_cast<int>(BLOCK * minimapScale);

                std::string mapHit;
                mapHit = map[j][i];
                Color c = Color(255, 0, 0);
                rect(minimapXCoord, minimapYCoord, mapHit, minimapBlock, minimapBlock);
            }
        }

    for (int i = 0; i < SCREEN_WIDTH; i++) {
      float a = player.a + player.fov / 2 - player.fov * i / minimapX;
      castR(a);
    }
    }

  }

  Player player;
private:
  int scale; // scale for rendering
  SDL_Renderer* renderer; // sdl render
  std::vector<std::string> map; //game map
  int tsize; // texture
};