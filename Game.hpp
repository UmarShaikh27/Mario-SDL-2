// #pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include "Utility.hpp"
#include "Timer.hpp"
#include "Mario.hpp"
#include "Obstaclegenerator.hpp"
#include "Obstacle.hpp"

class Game
{
    // Screen dimension constants
    const int SCREEN_WIDTH = 1000;
    const int SCREEN_HEIGHT = 600;

    // The window we'll be rendering to
    SDL_Window *gWindow = NULL;

    // The window renderer
    SDL_Renderer *gRenderer = NULL;

    // Current displayed texture
    SDL_Texture *gTexture = NULL;
    // global reference to png image sheets
    SDL_Texture *assets = NULL;
    Mix_Music *bgMusic = NULL;
    

public:
    bool init();
    bool loadMedia();
    void drawBg();    
    void close();
    void run();
    SDL_Texture* whitetexture=NULL;
    SDL_Texture* greentexture=NULL;
    ObstacleGenerator* obstacleGen;
    SDL_Rect greenSRCrect={0,0,396,497};
	SDL_Rect whiteSRCrect={0,0,396,497};
	SDL_Rect greenMoverRect={10,10,300,30};
	SDL_Rect whiteMoverRect={7,7,306,36};
};


