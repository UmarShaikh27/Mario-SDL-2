 #pragma once
#include <SDL.h>
#include "Obstacle.hpp"
#include "Utility.hpp"

class Snake:public Obstacle{

public:
    Snake(SDL_Renderer* renderer, int x, int y) : Obstacle(renderer,x,y)
    {
        // Load the obstacle texture , set source and mover rectangles
        obstacleTexture = Utility::loadTexture(renderer,"Images/obstacles2.png");
        srcRect = &srcOne;
        obstacleRect = {x, y, srcRect->w, srcRect->h};
        
    }

    void render()
    {
        SDL_RenderCopy(renderer, obstacleTexture, srcRect, &obstacleRect);
        obstacleRect.x-=3;
        srcRect = (srcRect == &srcOne)? &srcTwo: (srcRect == &srcTwo)? &srcThree:(srcRect == &srcThree)? &srcFour: &srcOne;

    }
private:
    SDL_Rect srcOne = {152,447,38,47};
    SDL_Rect srcTwo = {102,447,38,47};
    SDL_Rect srcThree = {52,447,38,47};
    SDL_Rect srcFour = {6,447,31,47};

};