#pragma once
#include <SDL.h>
#include "Utility.hpp"

class Obstacle
{
public:
    Obstacle(SDL_Renderer* renderer, int x, int y) : renderer(renderer), x(x), y(y)
    {
        // Load the obstacle texture (replace with actual image path)
        obstacleTexture = Utility::loadTexture(renderer,"Images/sprsheet.png");
        srcRect = &srcOne;
        obstacleRect = {x, y, srcRect->w, srcRect->h};
        
    }

    void render()
    {
        SDL_RenderCopy(renderer, obstacleTexture, srcRect, &obstacleRect);
        if(obstacleRect.x>0){
            obstacleRect.x-=4;
        }
        if(srcRect == &srcOne){
            srcRect = &srcTwo;
        }
        else{
            srcRect = &srcOne;
        }
    }

    // SDL_Rect Obstacle::getBoundingBox() const
    // {
    //     return {x, y, srcRect->w, srcRect->h};
    // }
// private:
    SDL_Renderer* renderer;
    int x, y;
    SDL_Texture* obstacleTexture;
    SDL_Rect srcOne = {8,289,44,26};
    SDL_Rect srcTwo = {7,324,24,28};
    SDL_Rect obstacleRect;
    SDL_Rect* srcRect;
};