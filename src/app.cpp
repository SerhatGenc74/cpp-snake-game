#include <iostream>
#include "Game.h"

int main (int argc,char* argv[])
{

    Game game;
    if (!game.Init("Snake Game",640,1280))
    {
        return -1;
    }
    
    game.Run();

    return 0;
}