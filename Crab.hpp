#pragma once
#include <SDL.h>
#include "Obstacle.hpp"
#include "Utility.hpp"

/**
 * Crab class
 * Ground-based enemy that:
 * - Moves along ground level
 * - Has sideways walking animation
 * - Moves at consistent speed
 * - Inherits base behavior from Obstacle
 */
class Crab : public Obstacle {

public:
    /**
     * Constructor: Sets up crab's sprite sheet and animation
     * @param renderer SDL rendering context
     * @param x Initial X position
     * @param y Initial Y position (generally ground level)
     */
    Crab(SDL_Renderer* renderer, int x, int y) : Obstacle(renderer,x,y)
    {
        // Load the obstacle texture , set source and mover rectangles
        obstacleTexture = Utility::loadTexture(renderer,"Images/obstacles2.png");
        srcRect = &srcOne;
        obstacleRect = {x, y, srcRect->w, srcRect->h};
    }

    /**
     * Render the crab and update its animation/position
     * - Moves left at constant speed
     * - Cycles through five walking animation frames
     */
    void render()
    {
        SDL_RenderCopy(renderer, obstacleTexture, srcRect, &obstacleRect);
        obstacleRect.x-=8;
        srcRect = (srcRect == &srcOne)? &srcTwo: (srcRect == &srcTwo)? &srcThree:(srcRect == &srcThree)? &srcFour: (srcRect == &srcFour)? &srcFive: &srcOne;
    }

private:
    // Animation frame coordinates from sprite sheet
    SDL_Rect srcOne = {40,123,32,25};     // Start of walk cycle
    SDL_Rect srcTwo = {5,160,32,32};      // Walking frame 2
    SDL_Rect srcThree = {45,160,32,32};   // Walking frame 3
    SDL_Rect srcFour = {235,160,32,32};   // Walking frame 4
    SDL_Rect srcFive = {195,160,32,32};   // Final walking frame
};