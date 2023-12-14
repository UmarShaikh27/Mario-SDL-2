#include <SDL.h>
#include <vector>
#include "Coin.hpp"


class CoinGenerator
{
public:
    CoinGenerator(SDL_Renderer* renderer, int screenWidth, int screenHeight) : renderer(renderer), screenWidth(screenWidth), screenHeight(screenHeight)
    {
    }
    void generateCoins(int numCoins)
    {
        for (int i = 0; i < numCoins; ++i)
        {
            int coinX = rand() % screenWidth;
            int coinY = 300 + (rand() % 110);

            // Generate different obstacle classes randomly
            int coinType = 0;
            // int coinType = rand() % 4;
            switch (coinType)
            {
            case 0:
                coins->push_back(Coin(renderer, coinX+lastCoinX, coinY));
                lastCoinX+=coinX;
                break;
            }
        }
    }
    bool renderCoins(SDL_Rect marioRect)
    {
        bool check = false;
        for (auto& coin : *coins)
        {
            coin.render();
            if (SDL_HasIntersection(&marioRect, coin.getBoundingBox() ))
            {
                check =  true;
            }
            
        }
        return check;
    }
    void scrollCoins(int scrollingOffset){
        for (auto& coin : *coins)
        {   
            coin.scrollWithBackground(scrollingOffset);    
        }
    }
    

private:
    SDL_Renderer* renderer;
    int screenWidth, screenHeight;
    std::vector<Coin> *coins = new std::vector<Coin>;
    //x position of the the last coin
    int lastCoinX = 0;
};