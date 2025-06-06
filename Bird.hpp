#pragma once
#include <SDL.h>
#include "Obstacle.hpp"
#include "Utility.hpp"

/**
 * Bird class
 * Flying enemy type that:
 * - Moves at a moderate speed
 * - Animates through flight cycles
 * - Appears at variable heights
 * - Inherits base behavior from Obstacle
 */
class Bird : public Obstacle {
public:
    /**
     * Constructor: Sets up bird's sprite sheet and animation
     * @param renderer SDL rendering context
     * @param x Initial X position
     * @param y Initial Y position (varies for flight height)
     */
    Bird(SDL_Renderer* renderer, int x, int y) : Obstacle(renderer,x,y)
    {
        // Load the obstacle texture , set source and mover rectangles
        obstacleTexture = Utility::loadTexture(renderer,"Images/obastacle3.png");
        srcRect = &srcOne;
        obstacleRect = {x, y, srcRect->w, srcRect->h};
        
    }

    /**
     * Render the bird and update its animation/position
     * - Moves left at constant speed
     * - Cycles through six flight animation frames
     */
    void render()
    {
        SDL_RenderCopy(renderer, obstacleTexture, srcRect, &obstacleRect);
        obstacleRect.x-=5;
        srcRect = (srcRect == &srcOne)? &srcTwo: (srcRect == &srcTwo)? &srcThree:(srcRect == &srcThree)? &srcFour: (srcRect == &srcFour)? &srcFive: (srcRect == &srcFive)? &srcSix: &srcOne;
    }

private:
    // Animation frame coordinates from sprite sheet
    SDL_Rect srcOne = {162,161,32,48};    // Wing up position
    SDL_Rect srcTwo = {119,166,38,38};    // Wings mid position
    SDL_Rect srcThree = {79,170,38,29};   // Wings down position
    SDL_Rect srcFour = {39,169,38,31};    // Wings spread
    SDL_Rect srcFive = {1,165,34,39};     // Wings folding
    SDL_Rect srcSix = {159,217,38,36};    // Return to start
};