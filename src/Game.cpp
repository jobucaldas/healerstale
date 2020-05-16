#include "Game.h"

Game::Game(char* gameName, int fullscreen)
{
    window = new Window(gameName, fullscreen);

    ChangeScene(CREDITS);
}