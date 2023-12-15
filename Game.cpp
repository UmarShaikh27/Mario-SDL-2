// DO NOT CHANGE THIS FILE
#include "Game.hpp"
bool Game::init()
{
	// Initialization flag
	bool success = true;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		// Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		// Create window
		gWindow = SDL_CreateWindow("HU Mania", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			// Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				// Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				// Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
                if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
				{
					printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool Game::loadMedia()
{
	// Loading success flag
	bool success = true;

	assets = Utility::loadTexture(gRenderer,"Images/sprsheet.png");
	gTexture = Utility::loadTexture(gRenderer,"Images/parallax.png");
	greentexture=Utility::loadTexture(gRenderer,"Images/green.png");
	whitetexture=Utility::loadTexture(gRenderer,"Images/white.png");
    bgMusic = Mix_LoadMUS( "Music/ThemeSong.wav" );

	if (assets == NULL || gTexture == NULL || greentexture ==NULL || whitetexture == NULL)
	{
		printf("Unable to run due to error: %s\n", SDL_GetError());
		success = false;
	}
    if(bgMusic == NULL){
		printf("Unable to load music: %s \n", Mix_GetError());
		success = false;
	}
	// jumpSound = Mix_LoadWAV("Music/smb_jump.wav"); // Replace with the actual path to your jump sound
	// if (jumpSound == nullptr)
	// {
	// 	printf("Failed to load jump sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	// 	success = false;
	// }
	return success;
}

void Game::close()
{
	// Free loaded images
	SDL_DestroyTexture(assets);
	assets = NULL;
	SDL_DestroyTexture(gTexture);

	// Destroy window
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
    Mix_FreeMusic(bgMusic);
	// Mix_FreeChunk(jumpSound);
	bgMusic = NULL;
	gWindow = NULL;
	gRenderer = NULL;
	// jumpSound = NULL;
	// Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
    Mix_Quit();
}

void Game::drawBg(){
	SDL_RenderClear(gRenderer);
	SDL_RenderCopy(gRenderer, gTexture, NULL, NULL); 
	SDL_RenderPresent(gRenderer);

}

void Game::run()
{
	bool quit = false;
	SDL_Event e;
    int scrollingOffset = 0;
    
    SDL_Rect healthRect = {10,10,300,30};
    SDL_Rect moverRect = {50,410,50,90};
    Mario* mario =  new Mario(moverRect,healthRect);
    const Uint8* keyState;
    obstacleGen =  new ObstacleGenerator(gRenderer,SCREEN_WIDTH,SCREEN_HEIGHT);
    coinGen =  new CoinGenerator(gRenderer,SCREEN_WIDTH,SCREEN_HEIGHT);
	obstacleGen->generateObstacles(3);
	coinGen->generateCoins(50);
	// Obstacle obs(gRenderer,300,200);



	while (!quit)
	{
		// Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			// User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}

            if( Mix_PlayingMusic() == 0 )
            {
                //Play the music
                // Mix_PlayMusic( bgMusic, 2 );
            }
		}
        keyState = SDL_GetKeyboardState(NULL);
        if(keyState[SDL_SCANCODE_LEFT]){
            mario->changeState();
            if(mario->moverRect.x>0){
                mario->moverRect.x -= 10;
            }
        }
        if(keyState[SDL_SCANCODE_RIGHT]){
            mario->changeState();
            if(mario->moverRect.x+mario->moverRect.w<1000){
                if(mario->moverRect.x<350){
                    mario->moverRect.x += 10;
                }else{
                    scrollingOffset -= 8; // Adjust the scrolling speed as needed
					coinGen->scrollCoins(scrollingOffset);
					obstacleGen->scrollObstacles(scrollingOffset);
                }
            }
        }
        if(keyState[SDL_SCANCODE_UP]){
            mario->makeJump();
			// Mix_PlayChannel(-1, jumpSound, 0);
        }
        if(keyState[SDL_SCANCODE_V]){
            mario->decreaseHealth();
        }
        
       
        mario->checkjump();

		
        // drawBg();

        ////////////////////////////////////////////////////////////////////////////

        // Render the background texture at the current scrolling offset
        SDL_Rect renderQuad = { scrollingOffset, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
        SDL_RenderClear(gRenderer);
        SDL_RenderCopy(gRenderer, gTexture, NULL, &renderQuad);

        // Render a second copy of the background texture to create the continuous scrolling effect
        SDL_Rect renderQuad2 = { scrollingOffset + SCREEN_WIDTH, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
        SDL_RenderCopy(gRenderer, gTexture, NULL, &renderQuad2);

		if(obstacleGen->renderObstacles(mario->moverRect)){
			mario->makeJump();
			mario->decreaseHealth();
		};
		
		if(coinGen->renderCoins(mario->moverRect)){	
			mario->increaseScore();
		};
		


        // Check if the first copy of the texture has scrolled completely off-screen
        if (scrollingOffset <= -SCREEN_WIDTH)
        {
            scrollingOffset = 0;
        }

        // SDL_RenderPresent(gRenderer);
        ////////////////////////////////////////////////////////////////////////////

		// SDL_RenderClear(gRenderer); // removes everything from renderer
		// SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);//Draws background to renderer
        SDL_RenderCopy(gRenderer, assets, &mario->Data->srcRect , &mario->moverRect);
        SDL_RenderCopy(gRenderer, whitetexture, &whiteSRCrect, &whiteMoverRect );
        SDL_RenderCopy(gRenderer, greentexture, &greenSRCrect, &mario->healthrect );

		//***********************draw the objects here********************


		//****************************************************************
		SDL_RenderPresent(gRenderer); // displays the updated renderer

		SDL_Delay(50); // causes sdl engine to delay for specified miliseconds
	}
}
