#pragma once
#include <SDL.h>
#include "Utility.hpp"

/**
 * Coin class
 * Represents collectible items in the game that:
 * - Animate through multiple frames
 * - Can be collected by the player for points
 * - Move with the scrolling background
 * - Handle their own rendering and collision detection
 */
class Coin
{
public:
    /**
     * Constructor: Initialize coin with position and renderer
     * Loads coin texture and sets up initial animation state
     */
    Coin(SDL_Renderer* renderer, int x, int y) : renderer(renderer), x(x), y(y)
    {
        coinTexture = Utility::loadTexture(renderer,"Images/coin.png");
        srcRect = &srcOne;
        coinRect = {x, y, 40, 40};
    }

    /**
     * Render the coin and update its animation
     * Cycles through six different sprite frames
     */
    void render()
    {
        SDL_RenderCopy(renderer, coinTexture, srcRect, &coinRect);
        //animate
        srcRect = (srcRect == &srcOne)? &srcTwo: (srcRect == &srcTwo)? &srcThree:(srcRect == &srcThree)? &srcFour: (srcRect == &srcFour)? &srcFive: (srcRect == &srcFive)? &srcSix: &srcOne;
        
    }

    /**
     * Get collision rectangle for coin collection detection
     */
    SDL_Rect* getBoundingBox()
    {
        return &coinRect;
    }

    /**
     * Update coin position when background scrolls
     * Moves coin left to maintain relative position
     */
    void scrollWithBackground(int offset)
    {
        coinRect.x -= 9;
    }
private:
    SDL_Renderer* renderer;          // Rendering context
    int x, y;                       // Position coordinates
    SDL_Texture* coinTexture;       // Coin sprite sheet
    
    // Animation frame source rectangles
    SDL_Rect srcOne = {20,40,170,170};    // Frame 1 of spinning animation
    SDL_Rect srcTwo = {230,40,130,170};   // Frame 2
    SDL_Rect srcThree = {450,40,80,170};  // Frame 3
    SDL_Rect srcFour = {670,40,40,170};   // Frame 4
    SDL_Rect srcFive = {860,40,80,170};   // Frame 5
    SDL_Rect srcSix = {1040,40,130,170};  // Frame 6
    
    SDL_Rect coinRect;              // Position and size rectangle
    SDL_Rect* srcRect;              // Current animation frame
};