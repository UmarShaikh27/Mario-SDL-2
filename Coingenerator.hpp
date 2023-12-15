#include <SDL.h>
#include <vector>
#include <list>
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
                Coin* coin =  new Coin(renderer, coinX+lastCoinX, coinY); 
                coins.push_back(coin);
                lastCoinX+=coinX;
                break;
            }
        }
    }
    bool renderCoins(SDL_Rect marioRect)
    {
        bool check = false;
        for (auto& coin : coins)
        {
            coin->render();
            if (SDL_HasIntersection(&marioRect, coin->getBoundingBox() ))
            {
                coins.remove(coin);
                delete coin;
                coin = nullptr;
                cout<<"coin deleted"<<endl;
                check =  true;
            }
            else if(coin->getBoundingBox()->x <-10){
                coins.remove(coin);
                delete coin;
                coin = nullptr;
                cout<<"coin deleted"<<endl;
                
            }
            
        }
        return check;
    }
    void scrollCoins(int scrollingOffset){
        for (auto& coin : coins)
        {   
            coin->scrollWithBackground(scrollingOffset);    
        }
    }
    

private:
    SDL_Renderer* renderer;
    int screenWidth, screenHeight;
    list<Coin*> coins; 
    //x position of the the last coin
    int lastCoinX = 0;
};