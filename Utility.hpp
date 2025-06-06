#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <SDL_mixer.h>

/**
 * Utility class
 * Provides static helper functions for common SDL operations
 * Currently handles:
 * - Texture loading from image files
 * - Error reporting for texture loading failures
 */
class Utility
{
public:
    /**
     * Load an image file into an SDL texture
     * Handles both image loading and texture creation
     * Reports errors if either step fails
     * 
     * @param renderer SDL rendering context to create texture in
     * @param path File path to the image to load
     * @return SDL_Texture* The loaded texture, or nullptr if loading failed
     */
    static SDL_Texture* loadTexture(SDL_Renderer* renderer, std::string path)
    {
        SDL_Texture* newTexture = nullptr;
        SDL_Surface* loadedSurface = IMG_Load(path.c_str());

        if (loadedSurface == nullptr)
        {
            printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
        }
        else
        {
            newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
            if (newTexture == nullptr)
            {
                printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
            }

            SDL_FreeSurface(loadedSurface);
        }

        return newTexture;
    } 
};