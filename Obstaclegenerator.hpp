#include <SDL.h>
#include <vector>
#include "Obstacle.hpp"

class ObstacleGenerator
{
public:
    ObstacleGenerator(SDL_Renderer* renderer, int screenWidth, int screenHeight) : renderer(renderer), screenWidth(screenWidth), screenHeight(screenHeight)
    {
    }
    void generateObstacles(int numObstacles)
    {
        for (int i = 0; i < numObstacles; ++i)
        {
            int obstacleX = rand() % screenWidth;
            int obstacleY = rand() % screenHeight;
            SDL_Rect srcRect = {0, 0, 50, 50}; // Adjust the size of the source rectangle

            // Generate different obstacle classes randomly
            int obstacleType = 0;
            // int obstacleType = rand() % 4;
            switch (obstacleType)
            {
            case 0:
                obstacles->push_back(Obstacle(renderer, obstacleX, obstacleY));
                break;
            // case 1:
            //     obstacles.push_back(Obstacle2(renderer, obstacleX, obstacleY, srcRect));
            //     break;
            // case 2:
            //     obstacles.push_back(Obstacle3(renderer, obstacleX, obstacleY, srcRect));
            //     break;
            // case 3:
            //     obstacles.push_back(Obstacle4(renderer, obstacleX, obstacleY, srcRect));
            //     break;
            }
        }
    }
    bool renderObstacles(SDL_Rect marioRect)
    {
        bool check = false;
        for (auto& obstacle : *obstacles)
        {
            obstacle.render();
            if (SDL_HasIntersection(&marioRect, obstacle.getBoundingBox() ))
            {
                // Handle collision (e.g., decrease health or take appropriate action)
                check =  true;
            }
            
        }
        return check;
    }
    

private:
    SDL_Renderer* renderer;
    int screenWidth, screenHeight;
    std::vector<Obstacle> *obstacles = new vector<Obstacle>;
};