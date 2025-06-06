#pragma once
#include <SDL.h>

/**
 * Playerstates structure
 * Manages Mario's animation states by storing sprite sheet coordinates
 * Contains rectangles for:
 * - Current animation frame (srcRect)
 * - Three walking animation frames (walkOne, walkTwo, walkThree)
 * Used to cycle through walking animations and update player appearance
 */
struct Playerstates {
    SDL_Rect srcRect;      // Current sprite sheet region to display
    SDL_Rect walkOne;      // First walking animation frame
    SDL_Rect walkTwo;      // Second walking animation frame
    SDL_Rect walkThree;    // Third walking animation frame
    
    // Default constructor
    Playerstates() = default;
    
    /**
     * Initialize animation states with sprite sheet coordinates
     * @param srcRect Initial sprite region
     * @param walkOne First walking frame region
     * @param walkTwo Second walking frame region
     * @param walkThree Third walking frame region
     */
    Playerstates(SDL_Rect srcRect, SDL_Rect walkOne, SDL_Rect walkTwo, SDL_Rect walkThree):
        srcRect(srcRect),
        walkOne(walkOne),
        walkTwo(walkTwo),
        walkThree(walkThree)
    {}
};