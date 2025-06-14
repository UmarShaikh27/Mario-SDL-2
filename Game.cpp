// DO NOT CHANGE THIS FILE
#include "Game.hpp"

/**
 * Initialize SDL subsystems and create window/renderer
 * Sets up: Video, Image loading, Audio, Window, Renderer
 */
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

/**
 * Load all game assets
 * - Sprite sheets
 * - Background textures
 * - Audio files (music and sound effects)
 * - UI elements (health bar textures)
 */
bool Game::loadMedia()
{
	// Loading success flag
	bool success = true;

    // Load sprite sheet and background textures
    assets = Utility::loadTexture(gRenderer,"Images/sprsheet.png");
    gTexture = Utility::loadTexture(gRenderer,"Images/Game_on.png");
    greentexture=Utility::loadTexture(gRenderer,"Images/green.png");
    whitetexture=Utility::loadTexture(gRenderer,"Images/white.png");

    // Load audio assets
    bgMusic = Mix_LoadMUS( "Music/ThemeSong.wav" );
	gameWonSound = Mix_LoadWAV("Music/smb_world_clear.wav");
	gameLostSound = Mix_LoadWAV("Music/smb_gameover.wav");

    // Verify all assets loaded successfully
    if (assets == NULL || gTexture == NULL || greentexture ==NULL || whitetexture == NULL)
    {
        printf("Unable to run due to error: %s\n", SDL_GetError());
        success = false;
    }
    if(bgMusic == NULL){
        printf("Unable to load music: %s \n", Mix_GetError());
        success = false;
    }
    return success;
}

// Clean up resources and shut down SDL subsystems
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

// Render the background texture
void Game::drawBg(){
	SDL_RenderClear(gRenderer);
	SDL_RenderCopy(gRenderer, gTexture, NULL, NULL); 
	SDL_RenderPresent(gRenderer);

}

// Main game loop
bool Game::run()
{
	bool quit = false;
	SDL_Event e;
    int scrollingOffset = 0;
	bool won=false;
    
    // Initialize game objects
    SDL_Rect healthRect = {10,10,300,30};
    SDL_Rect moverRect = {50,410,50,90};
    Mario* mario =  new Mario(moverRect,healthRect);
    const Uint8* keyState;

    // Create and initialize obstacles and coins
    obstacleGen =  new ObstacleGenerator(gRenderer,SCREEN_WIDTH,SCREEN_HEIGHT);
    coinGen =  new CoinGenerator(gRenderer,SCREEN_WIDTH,SCREEN_HEIGHT);
	obstacleGen->generateObstacles(50);
	coinGen->generateCoins(50);

    // Main game loop
	while (!quit)
	{
		// Handle input events
		while (SDL_PollEvent(&e) != 0)
		{
			// User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
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
                    // Scroll the level when player reaches screen boundary
                    scrollingOffset -= 8;
					coinGen->scrollCoins(scrollingOffset);
					obstacleGen->scrollObstacles(scrollingOffset);
                }
            }
        }
        if(keyState[SDL_SCANCODE_UP]){
            mario->makeJump();
        }
        
        mario->checkjump();

        // Render scrolling background
        SDL_Rect renderQuad = { scrollingOffset, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
        SDL_RenderClear(gRenderer);
        SDL_RenderCopy(gRenderer, gTexture, NULL, &renderQuad);

        // Render a second copy of the background texture to create the continuous scrolling effect
        SDL_Rect renderQuad2 = { scrollingOffset + SCREEN_WIDTH, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
        SDL_RenderCopy(gRenderer, gTexture, NULL, &renderQuad2);

        // Check collisions and update game state
		if(obstacleGen->renderObstacles(mario->moverRect)){
			if(mario->decreaseHealth()){
				quit=true;
			}
		}

		if(coinGen->renderCoins(mario->moverRect)){
			if(mario->increaseScore()){
				quit=true;
				won = true;
			}	
			
		};
		


        // Check if the first copy of the texture has scrolled completely off-screen
        if (scrollingOffset <= -SCREEN_WIDTH)
        {
            scrollingOffset = 0;
        }

        // Render game objects
        SDL_RenderCopy(gRenderer, assets, &mario->Data->srcRect , &mario->moverRect);
        SDL_RenderCopy(gRenderer, whitetexture, &whiteSRCrect, &whiteMoverRect );
        SDL_RenderCopy(gRenderer, greentexture, &greenSRCrect, &mario->healthrect );

		SDL_RenderPresent(gRenderer);
		SDL_Delay(50); // causes sdl engine to delay for specified miliseconds
	}

	if(won){
		cout<<"Game won"<<endl;
		return true;
		
	}else{
		cout<<"Game lost"<<endl;
		return false;
	}
}

// Handle startup/title screen
void Game::startup(){
	bool quit = false;
	SDL_Event e;
	
	// Title screen loop - wait for 'P' to start
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
			if(e.type == SDL_KEYDOWN) {
				SDL_Keycode symbol = e.key.keysym.sym;
				if(symbol == SDLK_p){
					quit=true;
				}
				else{
					cout<<"Invalid key"<<endl;
				}
			}

            // Loop background music
            if(Mix_PlayingMusic() == 0)
            {
                Mix_PlayMusic(bgMusic, 2);
            }
		}
		this->drawBg();
	}
	// Load game background after title screen
	gTexture = Utility::loadTexture(gRenderer,"Images/parallax.png");
}

/**
 * Game over screen handler
 * - Cleans up game objects
 * - Shows win/lose screen
 * - Plays victory/defeat sound
 * - Handles restart ('R') or quit ('Q')
 * Returns: true if player wants to restart
 */
bool Game::gamefinished(bool won){
	obstacleGen->~ObstacleGenerator();
	coinGen->~CoinGenerator();
	delete mario;
	mario =  nullptr;
	
	if(won){
		gTexture = Utility::loadTexture(gRenderer,"Images/game_won.jpg");
		Mix_PlayChannel(-1, gameWonSound, 0);
	}else{
		gTexture = Utility::loadTexture(gRenderer,"Images/game-over.jpg");
		Mix_PlayChannel(-1, gameLostSound, 0);
	}
	// Mix_FreeMusic(bgMusic);
	
	bool quit = false;
	bool restart = false;
	SDL_Event e;
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
			if(e.type == SDL_KEYDOWN) {
				SDL_Keycode symbol = e.key.keysym.sym;
				if(symbol == SDLK_q){
					quit=true;
				}
				else if(symbol == SDLK_r){
					quit=true;
					restart = true;
				}
				else{
					cout<<"Invalid key"<<endl;
				}
			}

            if( Mix_PlayingMusic() == 0 )
            {
                Mix_PlayMusic(bgMusic, 2);
            }
		}
		this->drawBg();
	}	return restart;
}