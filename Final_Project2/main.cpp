#include <iostream>
#include "game.h"

using namespace std;

int main()
{
    //init game engine
    Game game;

    while(game.running()){

        //game update
        game.update();

        //game render

        game.render();
    }



    return 0;
}
