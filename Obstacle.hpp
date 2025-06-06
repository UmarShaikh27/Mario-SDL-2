#pragma once
#include <SDL.h>
#include "Utility.hpp"

/**
 * Obstacle base class
 * Abstract base class for all game obstacles/enemies
 * Provides common functionality for:
 * - Texture loading and rendering
 * - Position tracking and collision detection
 * - Background scrolling behavior
 */
class Obstacle
{
public:
    /**
     * Constructor: Initialize obstacle with position and rendering context
     * @param renderer SDL rendering context
     * @param x Initial X position
     * @param y Initial Y position
     */
    Obstacle(SDL_Renderer* renderer, int x, int y) : renderer(renderer), x(x), y(y)
    {
        // Load the obstacle texture , set source and mover rectangles
        obstacleTexture = Utility::loadTexture(renderer,"Images/sprsheet.png");
    }
    
    /**
     * Pure virtual render function
     * Each obstacle type must implement its own rendering logic
     */
    virtual void render(){};

    /**
     * Get collision rectangle for obstacle
     * Used for intersection testing with player
     */
    SDL_Rect* getBoundingBox()
    {
        return &obstacleRect;
    }

    /**
     * Update obstacle position when background scrolls
     * @param offset Amount of scroll movement
     */
    void scrollWithBackground(int offset)
    {
        obstacleRect.x -= 7;
    }

protected:
    SDL_Renderer* renderer;          // Rendering context
    int x, y;                       // Position coordinates
    SDL_Texture* obstacleTexture;   // Sprite sheet texture
    SDL_Rect obstacleRect;          // Collision/position rectangle
    SDL_Rect* srcRect;              // Source rectangle for sprite sheet
};