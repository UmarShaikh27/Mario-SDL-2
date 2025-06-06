#include <SDL.h>
#include <iostream>
#include <vector>
#include <list>
#include "Obstacle.hpp"
#include "Parrot.hpp"
#include "Crab.hpp"
#include "Snake.hpp"
#include "Bird.hpp"
using namespace std;

/**
 * ObstacleGenerator class
 * Manages the creation and behavior of game obstacles:
 * - Generates different types of enemies (Parrot, Crab, Snake, Bird)
 * - Handles obstacle positioning and movement
 * - Manages collision detection with player
 * - Handles obstacle recycling when they move off-screen
 */
class ObstacleGenerator
{
public:
    /**
     * Constructor: Initializes obstacle generator with rendering context and screen dimensions
     */
    ObstacleGenerator(SDL_Renderer* renderer, int screenWidth, int screenHeight) : renderer(renderer), screenWidth(screenWidth), screenHeight(screenHeight)
    {
    }

    /**
     * Generates a specified number of random obstacles
     * Different types of obstacles are placed at appropriate heights:
     * - Flying enemies (Parrot, Bird) at variable heights
     * - Ground enemies (Crab, Snake) at ground level
     */
    void generateObstacles(int numObstacles)
    {
        for (int i = 0; i < numObstacles; ++i)
        {
            //position of obstacle
            //X position is added with respect the position of the last obstacle created so that its created further away
            int obstacleX = 100+rand() % (screenWidth-100);
            int obstacleY = 300 + (rand() % 110);

            // Generate different obstacle classes randomly

            int obstacleType = rand() % 4;
            Obstacle* obs;
            if(obstacleType == 0){
                obs =  new Parrot(renderer, obstacleX + lastObstacleX, obstacleY);
            }else if(obstacleType == 1){
                obstacleY = 405 + (rand() % 6);
                obs =  new Crab(renderer, obstacleX + lastObstacleX, obstacleY);
            }else if(obstacleType == 2){
                obstacleY = 405 + (rand() % 6);
                obs =  new Snake(renderer, obstacleX + lastObstacleX, obstacleY);
            }else{
                obs =  new Bird(renderer, obstacleX + lastObstacleX, obstacleY);
            }

            obstacles.push_back(obs);
            lastObstacleX+=obstacleX;
            
        }
    }

    /**
     * Renders obstacles and handles:
     * - Collision detection with Mario
     * - Recycling off-screen obstacles
     * Returns: true if Mario collided with an obstacle
     */
    bool renderObstacles(SDL_Rect marioRect)
    {
        bool check = false;
        for (auto& obstacle : obstacles)
        {
            obstacle->render();
            //if obstacle collides with left hand side of the screen, it gets spawned randomly at the right again
            if(obstacle->getBoundingBox()->x < -15){
                obstacle->getBoundingBox()->x = 1000 + rand() % 500;
            }
            //collision check
            if (SDL_HasIntersection(&marioRect, obstacle->getBoundingBox() ))
            {
                obstacles.remove(obstacle);
                delete obstacle;
                obstacle = nullptr;
                cout<<"obstacle deleted"<<endl;
                check =  true;
            }
            
            
        }
        return check;
    }

    /**
     * Updates obstacle positions when background scrolls
     * Called when player moves right beyond screen midpoint
     */
    void scrollObstacles(int scrollingOffset){
        for (auto& obstacle : obstacles)
        {   
            obstacle->scrollWithBackground(scrollingOffset);    
        }
    }

    /**
     * Destructor: Cleans up all allocated obstacle objects
     */
    ~ObstacleGenerator(){
        for (auto& obstacle : obstacles)
        {   
            delete obstacle;
            obstacle = nullptr;   
        }
        cout<<"All obstacles deleted"<<endl;
    }

private:
    SDL_Renderer* renderer;          // Rendering context
    int screenWidth, screenHeight;   // Screen dimensions
    list<Obstacle*> obstacles;       // List of active obstacles
    int lastObstacleX = 1000;       // Starting X position for first obstacle
};