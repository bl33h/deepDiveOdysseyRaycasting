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
#include "colors.h"
#include "resourceManager.h"
#include <iostream>
#include <fstream>
#include <SDL_render.h>
#include <string>
#include <vector>
#include <cmath>
#include <SDL2/SDL.h>
#include <unordered_map>
#include <array>

struct Point {
  int x;
  int y;
};

const Color B = {245, 236, 255};
const Color W = {255, 255, 255};

const int WIDTH = 16;
const int HEIGHT = 11;
const int BLOCK = 50;
const int SCREEN_WIDTH = WIDTH * BLOCK;
const int SCREEN_HEIGHT = HEIGHT * BLOCK;
int minimapWidth = SCREEN_WIDTH / 4; 
int minimapHeight = SCREEN_HEIGHT / 4;
int minimapX = SCREEN_WIDTH - minimapWidth;
int minimapY = 0;

float minimapScale = 0.25f;

struct Player {
  int x;
  int y;
  float a;
  float fov;
}; 

struct Impact {
  float d;
  std::string mapHit;
  int tx;
};

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

  bool load_map(const std::string& filename) {
    std::ifstream file(filename);

    std::string line;
    while (getline(file, line)) {
      map.push_back(line);
    }

    file.close();
    return true;
  }

  void point(int x, int y, Color c) {
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
    SDL_RenderDrawPoint(renderer, x, y);
  }

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

  Impact cast_ray(float a) {
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

  void draw_stake(int x, float h, Impact i) {
    float start = SCREEN_HEIGHT/2.0f - h/2.0f;
    float end = start + h;

    for (int y = start; y < end; y++) {
      int ty = (y - start) * tsize / h;
      Color c = ResourceManager::getPixelColor(i.mapHit, i.tx, ty);
      SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);

      SDL_RenderDrawPoint(renderer, x, y);
    }
  }

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

  bool checkCollision(int x, int y) {
      int i = x / BLOCK;
      int j = y / BLOCK;
      return map[j][i] != ' ';
  }

  void render() {

    for (int i = 0; i < SCREEN_WIDTH; i++) {
      double a = player.a + player.fov / 2.0 - player.fov * i / SCREEN_WIDTH;
      Impact impact = cast_ray(a);
      float d = impact.d;
      Color c = Color(255, 0, 0);
      int x = i;
      float h = static_cast<float>(SCREEN_HEIGHT)/static_cast<float>(d) * static_cast<float>(scale);
      draw_stake(x, h, impact);
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
      cast_ray(a);
    }
    }

  }

  Player player;
private:
  int scale;
  SDL_Renderer* renderer;
  std::vector<std::string> map;
  int tsize;
};