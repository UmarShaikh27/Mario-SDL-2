#include "Game.hpp"

int main(int argc, char *argv[]){
    // Game game;
    // srand(time(NULL));
    // if( !game.init() ){
	// 	printf( "Failed to initialize!\n" );
    //     return 0;
	// }
	// 	//Load media
    // if( !game.loadMedia() ){
    //     printf( "Failed to load media!\n" );
    //     return 0;
    // }
    // game.startup();
    Game game;
    while (true){
        srand(time(NULL));
        game.init();
        game.loadMedia();
        game.startup();
        bool won = game.run();
        bool restart = game.gamefinished(won);
        if(!restart){break;}
    }
        game.close();
    
    // game.close();

    return 0;
}