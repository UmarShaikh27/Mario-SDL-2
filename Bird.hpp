 #pragma once
#include <SDL.h>
#include "Obstacle.hpp"
#include "Utility.hpp"

class Bird:public Obstacle{

public:
    Bird(SDL_Renderer* renderer, int x, int y) : Obstacle(renderer,x,y)
    {
        // Load the obstacle texture , set source and mover rectangles
        obstacleTexture = Utility::loadTexture(renderer,"Images/obastacle3.png");
        srcRect = &srcOne;
        obstacleRect = {x, y, srcRect->w, srcRect->h};
        
    }

    void render()
    {
        SDL_RenderCopy(renderer, obstacleTexture, srcRect, &obstacleRect);
        obstacleRect.x-=5;
        srcRect = (srcRect == &srcOne)? &srcTwo: (srcRect == &srcTwo)? &srcThree:(srcRect == &srcThree)? &srcFour: (srcRect == &srcFour)? &srcFive: (srcRect == &srcFive)? &srcSix: &srcOne;
    }
private:
    SDL_Rect srcOne = {162,161,32,48};
    SDL_Rect srcTwo = {119,166,38,38};
    SDL_Rect srcThree = {79,170,38,29};
    SDL_Rect srcFour = {39,169,38,31};
    SDL_Rect srcFive = {1,165,34,39};
    SDL_Rect srcSix = {159,217,38,36};

};