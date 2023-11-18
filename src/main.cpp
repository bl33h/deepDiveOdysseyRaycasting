/*---------------------------------------------------------------------------
Copyright (C), 2022-2023, Sara Echeverria (bl33h)
@author Sara Echeverria
FileName: main.cpp
@version: I
Creation: 06/11/2023
Last modification: 17/11/2023
*Some parts were made using the AIs Bard and ChatGPT
------------------------------------------------------------------------------*/
#include "resourceManager.h"
#include "constants.h"
#include "raycaster.h"
#include "colors.h"
#include "levels.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL_events.h>
#include <SDL_render.h>
#include <SDL_video.h>

int showMenu(SDL_Renderer* renderer) {
    int selectedOption = 0;
    int quitOption = levels.size();
    bool quit = false;

    TTF_Font* font = TTF_OpenFont("src/assets/Alphakind.ttf", 24);

    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    SDL_Color welcomeColor = { 40, 131, 154 };
    SDL_Surface* welcomeSurface = TTF_RenderText_Solid(font, "Choose a level and have fun (:", welcomeColor);
    SDL_Texture* welcomeTexture = SDL_CreateTextureFromSurface(renderer, welcomeSurface);
    SDL_Surface* backgroundSurface = IMG_Load("src/assets/screens/ddo.png");
    SDL_Texture* backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
    SDL_FreeSurface(backgroundSurface);

    int welcomeX = (windowWidth - welcomeSurface->w) / 2;
    int welcomeY = (windowHeight - welcomeSurface->h) / 2 - 50;

    while (!quit) {
        SDL_RenderClear(renderer);

        SDL_Rect welcomeRect = { welcomeX, welcomeY, welcomeSurface->w, welcomeSurface->h };
        SDL_RenderCopy(renderer, backgroundTexture, nullptr, nullptr);
        SDL_RenderCopy(renderer, welcomeTexture, nullptr, &welcomeRect);

        int menuY = windowHeight / 2;

        for (int i = 0; i < levels.size(); ++i) {
            SDL_Color textColor = { 93, 137, 148 };

            if (i == selectedOption) {
                textColor.r = 12;
                textColor.g = 71;
                textColor.b = 84;
            }

            SDL_Surface* textSurface = TTF_RenderText_Solid(font, levels[i].name.c_str(), textColor);
            if (textSurface) {
                int textX = (windowWidth - textSurface->w) / 2;
                int textY = menuY + i * 40;

                SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
                SDL_Rect textRect = { textX, textY, textSurface->w, textSurface->h };

                SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

                SDL_FreeSurface(textSurface);
                SDL_DestroyTexture(textTexture);
            }
        }

        SDL_Color exitColor = { 93, 137, 148 };
        if (selectedOption == quitOption) {
            exitColor.r = 12;
            exitColor.g = 71;
            exitColor.b = 84;
        }
        SDL_Surface* exitSurface = TTF_RenderText_Solid(font, "Exit", exitColor);
        int exitX = (windowWidth - exitSurface->w) / 2;
        int exitY = menuY + (levels.size() * 40);
        SDL_Texture* exitTexture = SDL_CreateTextureFromSurface(renderer, exitSurface);
        SDL_Rect exitRect = { exitX, exitY, exitSurface->w, exitSurface->h };
        SDL_RenderCopy(renderer, exitTexture, nullptr, &exitRect);
        SDL_FreeSurface(exitSurface);
        SDL_DestroyTexture(exitTexture);
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_UP) {
                    selectedOption = (selectedOption - 1 + (quitOption + 1)) % (quitOption + 1);
                } else if (event.key.keysym.sym == SDLK_DOWN) {
                    selectedOption = (selectedOption + 1) % (quitOption + 1);
                } else if (event.key.keysym.sym == SDLK_RETURN) {
                    if (selectedOption == quitOption) {
                        quit = true;
                    } else {
                        quit = true;
                    }
                }
            }
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(backgroundTexture);
    TTF_CloseFont(font);
    SDL_FreeSurface(welcomeSurface);
    SDL_DestroyTexture(welcomeTexture);
    return (selectedOption == quitOption) ? -1 : selectedOption;
}

void floor() {
  SDL_SetRenderDrawColor(renderer, 55, 80, 117, 255);
  SDL_Rect rect = {
    SCREEN_WIDTH, 
    SCREEN_WIDTH,
  };
  SDL_RenderFillRect(renderer, &rect);
}

void renderWinnerMessage() {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
  SDL_Surface* victoryImage = IMG_Load("src/assets/screens/ddoEnd.png");
  SDL_Texture* victoryTexture = SDL_CreateTextureFromSurface(renderer, victoryImage);
  SDL_Rect destRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
  SDL_RenderCopy(renderer, victoryTexture, NULL, &destRect);
  SDL_RenderPresent(renderer);
  SDL_Delay(5000);
  SDL_DestroyTexture(victoryTexture);
  SDL_FreeSurface(victoryImage);
  SDL_Quit();
}

void clear() {
  SDL_SetRenderDrawColor(renderer, 59, 107, 139, 255);
  SDL_RenderClear(renderer);
}

int main() {
  Uint32 lastTime = SDL_GetTicks();
  bool mouseCaptured = false;
  bool bubblesSound = false;
  bool running = true;
  int frameCount = 0;
  int speed = 10;
  int previousMouseX = 0;
  SDL_Rect playerRect;
  
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
  Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
  ResourceManager::init();

  window = SDL_CreateWindow("DDO by bl33h", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  ResourceManager::loadImage("-", "src/assets/objects/uw.png");
  ResourceManager::loadImage("|", "src/assets/objects/uw1.png");
  ResourceManager::loadImage("*", "src/assets/objects/uw2.png");
  ResourceManager::loadImage("+", "src/assets/objects/uw3.png");
  ResourceManager::loadImage(",", "src/assets/objects/uw4.png");
  ResourceManager::loadImage(".", "src/assets/objects/uw5.png");
  ResourceManager::loadImage("g", "src/assets/objects/treasure.png");
  ResourceManager::loadImage("p", "src/assets/objects/character.png");

    if (TTF_Init() == -1) {
        return 1;
    }

  int selectedLevel = showMenu(renderer);
    if (selectedLevel == -1) {
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 0;
    }

    if (selectedLevel < 0 || selectedLevel >= levels.size()) {
        return 1;
    }

    Raycaster r = { renderer };
    if (!r.load_map(levels[selectedLevel].mapFile)) {
        return 1;
    }

    Mix_Music* backgroundMusic = Mix_LoadMUS("src/assets/sounds/mikaUnderwater.mp3");
    marineWalking = Mix_LoadWAV("src/assets/sounds/bubbles.mp3");
    winner = Mix_LoadWAV("src/assets/sounds/marioBrosVida.mp3");
    turn = Mix_LoadWAV("src/assets/sounds/turn.mp3");

    if (backgroundMusic) {
        Mix_PlayMusic(backgroundMusic, -1);

  std::vector<SDL_Texture*> actionFrames;

    for (int i = 1; i <= 4; ++i) {
        std::string frameFileName = "src/assets/objects/character" + std::to_string(i) + ".png";
        SDL_Surface* actionFrameI = IMG_Load(frameFileName.c_str());
        SDL_Texture* actionFrameT = SDL_CreateTextureFromSurface(renderer, actionFrameI);
        SDL_FreeSurface(actionFrameI);
        actionFrames.push_back(actionFrameT);
    }

  while(running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        running = false;
        break;
      }

      if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
          mouseCaptured = true;
          previousMouseX = event.button.x;
      }

      if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT) {
          mouseCaptured = false;
      }

      if (mouseCaptured && event.type == SDL_MOUSEMOTION) {
          int mouseX = event.motion.x;
          int deltaX = mouseX - previousMouseX;
          float rotationSpeed = 0.00005f;
          if (deltaX < 0) {
              r.player.a -= 3.14/24;
          } else{
              r.player.a += 3.14/24;
          }
      }
      if (event.type == SDL_KEYDOWN) {
        switch(event.key.keysym.sym ){
          case SDLK_LEFT:
            r.player.a += 3.14/24;
            break;
          case SDLK_RIGHT:
            r.player.a -= 3.14/24;
            break;
        case SDLK_UP: {
            int nextX = r.player.x + speed * cos(r.player.a);
            int nextY = r.player.y + speed * sin(r.player.a);
            if (r.checkWinner()) {
                Mix_PlayChannel(-1, winner, 0);
                playerWon = true;
            }
            if (!r.checkCollision(nextX, nextY)) {
                Mix_PlayChannel(-1, marineWalking, 0);
                r.player.x = nextX;
                r.player.y = nextY;
            }
            break;
        }
        case SDLK_DOWN: {
            int nextX = r.player.x - speed * cos(r.player.a);
            int nextY = r.player.y - speed * sin(r.player.a);
            if (r.checkWinner()) {
                Mix_PlayChannel(-1, winner, 0);
                playerWon = true;
            }
            if (!r.checkCollision(nextX, nextY)) {
                Mix_PlayChannel(-1, turn, 0);
                r.player.x = nextX;
                r.player.y = nextY;
            }
            break;
        }
        
        case SDLK_SPACE:{
            if (!bubblesSound) {
                bubblesSound = true;
            }
            break;
        }
            default:
            break;
        }
      }
    }

    clear();
    floor();
    int size = 130;
    playerRect.x = SCREEN_WIDTH/2.0f - size/2.0f;
    playerRect.y = SCREEN_HEIGHT - size;
    playerRect.w = size;
    playerRect.h = size;
    if (playerWon) {
        renderWinnerMessage();

    } else {
        r.render();
        if (bubblesSound) {
            for (size_t i = 0; i < actionFrames.size(); ++i) {
                SDL_RenderCopy(renderer, actionFrames[i], nullptr, &playerRect);
                SDL_RenderPresent(renderer);
                SDL_Delay(100);
            }
            bubblesSound = false;
        } else {
        ResourceManager::render(renderer, "p",  SCREEN_WIDTH/2.0f - size/2.0f, SCREEN_HEIGHT - size, size);
        }
    }

    SDL_RenderPresent(renderer);
      frameCount++;
      Uint32 currentTime = SDL_GetTicks();
      Uint32 elapsedTime = currentTime - lastTime;
    if (elapsedTime >= 1000) {
        int fps = frameCount * 1000 / elapsedTime;
        std::string title = "DDO by bl33h - FPS: " + std::to_string(fps);
        SDL_SetWindowTitle(window, title.c_str());

        frameCount = 0;
        lastTime = currentTime;
    }
  }
    if (marineWalking) {
        Mix_FreeChunk(marineWalking);
        marineWalking = nullptr;
    }

    TTF_Quit();
    Mix_FreeMusic(backgroundMusic);
    Mix_CloseAudio();
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
    }
}