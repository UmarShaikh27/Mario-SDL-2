#include <SDL.h>
#include <vector>
#include <list>
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
            //position of obstacle
            //X position is added with the position of the last obstacle created so that its created further away
            int obstacleX = rand() % (screenWidth-300);
            int obstacleY = 300 + (rand() % 110);

            // Generate different obstacle classes randomly
            int obstacleType = 0;
            // int obstacleType = rand() % 4;
            switch (obstacleType)
            {
            case 0:
                Obstacle* obs =  new Obstacle(renderer, obstacleX + lastObstacleX, obstacleY);
                obstacles.push_back(obs);
                lastObstacleX+=obstacleX;
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
    void scrollObstacles(int scrollingOffset){
        for (auto& obstacle : obstacles)
        {   
            obstacle->scrollWithBackground(scrollingOffset);    
        }
    }
    

private:
    SDL_Renderer* renderer;
    int screenWidth, screenHeight;
    list<Obstacle*> obstacles;
    int lastObstacleX= 1000;
};