#pragma once
#include "Obstacle.hpp"
#include <SDL.h>
#include "Utility.hpp"

class Parrot:public Obstacle{

public:
    Parrot(SDL_Renderer* renderer, int x, int y) : Obstacle(renderer,x,y)
    {
        // Load the obstacle texture , set source and mover rectangles
        obstacleTexture = Utility::loadTexture(renderer,"Images/sprsheet.png");
        srcRect = &srcOne;
        obstacleRect = {x, y, srcRect->w, srcRect->h};
        
    }

    void render()
    {
        SDL_RenderCopy(renderer, obstacleTexture, srcRect, &obstacleRect);
        obstacleRect.x-=6;
        if(srcRect == &srcOne){
            srcRect = &srcTwo;
        }
        else{
            srcRect = &srcOne;
        }
    }
private:
    SDL_Rect srcOne = {8,289,44,26};
    SDL_Rect srcTwo = {7,324,24,28};
};