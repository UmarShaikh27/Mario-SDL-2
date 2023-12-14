#pragma once
#include <SDL.h>
#include "Utility.hpp"

class Coin
{
public:
    Coin(SDL_Renderer* renderer, int x, int y) : renderer(renderer), x(x), y(y)
    {
        coinTexture = Utility::loadTexture(renderer,"Images/coin.png");
        srcRect = &srcOne;
        coinRect = {x, y, 40, 40};
    }

    void render()
    {
        SDL_RenderCopy(renderer, coinTexture, srcRect, &coinRect);
        //animate
        srcRect = (srcRect == &srcOne)? &srcTwo: (srcRect == &srcTwo)? &srcThree:(srcRect == &srcThree)? &srcFour: (srcRect == &srcFour)? &srcFive: (srcRect == &srcFive)? &srcSix: &srcOne;
        
    }

    SDL_Rect* getBoundingBox()
    {
        return &coinRect;
    }
    void scrollWithBackground(int offset)
    {
        coinRect.x -= 12;
    }
private:
    SDL_Renderer* renderer;
    int x, y;
    SDL_Texture* coinTexture;
    SDL_Rect srcOne = {20,40,170,170};
    SDL_Rect srcTwo = {230,40,130,170};
    SDL_Rect srcThree = {450,40,80,170};
    SDL_Rect srcFour = {670,40,40,170};
    SDL_Rect srcFive = {860,40,80,170};
    SDL_Rect srcSix = {1040,40,130,170};
    SDL_Rect coinRect;
    SDL_Rect* srcRect;
};