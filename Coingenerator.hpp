#include <SDL.h>
#include <vector>
#include <list>
#include "Coin.hpp"

/**
 * CoinGenerator class
 * Manages the generation, rendering, and cleanup of collectible coins in the game.
 * - Creates coins at random positions
 * - Handles coin collection by player
 * - Manages coin scrolling with background
 * - Cleans up coins that move off-screen
 */
class CoinGenerator
{
public:
    /**
     * Constructor: Initializes coin generator with rendering context and screen dimensions
     */
    CoinGenerator(SDL_Renderer* renderer, int screenWidth, int screenHeight) : renderer(renderer), screenWidth(screenWidth), screenHeight(screenHeight)
    {
    }

    /**
     * Generates a specified number of coins at random positions
     * Coins are placed at varying heights and with increasing X distances
     */
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

    /**
     * Renders all coins and checks for collisions with Mario
     * Returns: true if Mario collected a coin, false otherwise
     */
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

    /**
     * Updates coin positions when background scrolls
     * Called when player moves right beyond screen midpoint
     */
    void scrollCoins(int scrollingOffset){
        for (auto& coin : coins)
        {   
            coin->scrollWithBackground(scrollingOffset);    
        }
    }

    /**
     * Destructor: Cleans up all allocated coin objects
     */
    ~CoinGenerator(){
        for (auto& coin : coins)
        {   
            delete coin;
            coin = nullptr;   
        }
        cout<<"All coins deleted"<<endl;
    }

private:
    SDL_Renderer* renderer;          // Rendering context
    int screenWidth, screenHeight;   // Screen dimensions
    list<Coin*> coins;              // List of active coins
    int lastCoinX = 0;              // X position of most recently generated coin
};