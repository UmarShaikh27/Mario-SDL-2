#pragma once
#include <SDL.h>
#include "Obstacle.hpp"
#include "Utility.hpp"

class Crab:public Obstacle{

public:
    Crab(SDL_Renderer* renderer, int x, int y) : Obstacle(renderer,x,y)
    {
        // Load the obstacle texture , set source and mover rectangles
        obstacleTexture = Utility::loadTexture(renderer,"Images/obstacles2.png");
        srcRect = &srcOne;
        obstacleRect = {x, y, srcRect->w, srcRect->h};
        
    }

    void render()
    {
        SDL_RenderCopy(renderer, obstacleTexture, srcRect, &obstacleRect);
        obstacleRect.x-=8;
        srcRect = (srcRect == &srcOne)? &srcTwo: (srcRect == &srcTwo)? &srcThree:(srcRect == &srcThree)? &srcFour: (srcRect == &srcFour)? &srcFive: &srcOne;
    }
private:
    SDL_Rect srcOne = {40,123,32,25};
    SDL_Rect srcTwo = {5,160,32,32};
    SDL_Rect srcThree = {45,160,32,32};
    SDL_Rect srcFour = {235,160,32,32};
    SDL_Rect srcFive = {195,160,32,32};
};