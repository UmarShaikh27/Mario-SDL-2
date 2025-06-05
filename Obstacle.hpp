#pragma once
#include <SDL.h>
#include "Utility.hpp"

class Obstacle
{
public:
    Obstacle(SDL_Renderer* renderer, int x, int y) : renderer(renderer), x(x), y(y)
    {
        // Load the obstacle texture , set source and mover rectangles
        obstacleTexture = Utility::loadTexture(renderer,"Images/sprsheet.png");
    }

    virtual void render(){};

    SDL_Rect* getBoundingBox()
    {
        return &obstacleRect;
    }
    void scrollWithBackground(int offset)
    {
        obstacleRect.x -= 7;
    }
protected:
    SDL_Renderer* renderer;
    int x, y;
    SDL_Texture* obstacleTexture;
    SDL_Rect obstacleRect;
    SDL_Rect* srcRect;
};