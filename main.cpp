#include "Game.hpp"

int main(int argc, char *argv[]){
    Game game;
    game.init();
    while (true){
        srand(time(NULL));
        game.loadMedia();
        game.startup();
        bool won = game.run();
        bool restart = game.gamefinished(won);
        if(!restart){break;}
    }
        game.close();
    return 0;
}