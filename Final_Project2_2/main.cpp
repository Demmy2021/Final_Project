#include <iostream>
#include "game.h"
#include <ctime>
#include <memory>

using namespace std;

int main()
{
    //init srand

    std::srand(static_cast<unsigned>(time(NULL)));

    //init game engine
    Game game;

    while(game.running() && !game.getEndGame()){


        //game update
        game.update();

        //game render

        game.render();
    }



    return 0;
}
