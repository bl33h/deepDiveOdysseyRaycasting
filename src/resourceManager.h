/*---------------------------------------------------------------------------
Copyright (C), 2022-2023, Sara Echeverria (bl33h)
@author Sara Echeverria
FileName: resourceManager.h
@version: I
Creation: 06/11/2023
Last modification: 17/11/2023
*Some parts were made using the AIs Bard and ChatGPT
------------------------------------------------------------------------------*/
#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdexcept>
#include <map>
#include <string>
#include "colors.h"

class ResourceManager {
private:
    static std::map<std::string, SDL_Surface*> imageSurfaces;
public:
    static void init() {
        int imgFlags = IMG_INIT_PNG;
    }
    static void loadImage(const std::string& key, const char* path) {
        SDL_Surface* newSurface = IMG_Load(path);
        imageSurfaces[key] = newSurface;
    }
    static Color getPixelColor(const std::string& key, int x, int y) {
        auto it = imageSurfaces.find(key);
        SDL_Surface* targetSurface = it->second;
        int bpp = targetSurface->format->BytesPerPixel;
        Uint8 *p = (Uint8 *)targetSurface->pixels + y * targetSurface->pitch + x * bpp;

        Uint32 pixelColor;
        switch (bpp) {
            case 1:
                pixelColor = *p;
                break;
            case 2:
                pixelColor = *(Uint16 *)p;
                break;
            case 3:
                if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
                    pixelColor = p[0] << 16 | p[1] << 8 | p[2];
                } else {
                    pixelColor = p[0] | p[1] << 8 | p[2] << 16;
                }
                break;
            case 4:
                pixelColor = *(Uint32 *)p;
                break;
            default:
                throw std::runtime_error("Unknown format!");
        }
        
        SDL_Color color;
        SDL_GetRGB(pixelColor, targetSurface->format, &color.r, &color.g, &color.b);
        return Color{color.r, color.g, color.b};
    }

    static void render(SDL_Renderer* renderer, const std::string& key, int x, int y, int size = -1) {
        auto it = imageSurfaces.find(key);

        SDL_Surface* targetSurface = it->second;
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, targetSurface);
        SDL_Rect destRect;
        if (size == -1){
            destRect = { x, y, targetSurface->w, targetSurface->h };
        } else{
            destRect = { x, y, size, size };
        }
        SDL_RenderCopy(renderer, texture, NULL, &destRect);
        SDL_DestroyTexture(texture);
    }

    static void cleanup() {
        for (auto& pair : imageSurfaces) {
            if (pair.second) {
                SDL_FreeSurface(pair.second);
            }
        }
        imageSurfaces.clear();
        IMG_Quit();
    }
};

std::map<std::string, SDL_Surface*> ResourceManager::imageSurfaces;