#pragma once
#include <SDL.h>
#include "Utility.hpp"

class Obstacle
{
public:
    Obstacle(SDL_Renderer* renderer, int x, int y, SDL_Rect srcRect) : renderer(renderer), x(x), y(y), srcRect(srcRect)
    {
        // Load the obstacle texture (replace with actual image path)
        obstacleTexture = Utility::loadTexture(renderer,"Images/obstacle.png");
    }

    void render()
    {
        SDL_Rect obstacleRect = {x, y, srcRect.w, srcRect.h};
        SDL_RenderCopy(renderer, obstacleTexture, &srcRect, &obstacleRect);
    }

private:
    SDL_Renderer* renderer;
    int x, y;
    SDL_Texture* obstacleTexture;
    SDL_Rect srcRect;
};