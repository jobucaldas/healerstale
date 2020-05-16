#ifndef GAME_H
#define GAME_H

// SDL
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

// C++
#include <iostream>

// Engine
#include "Engine/Scene.h"
#include "Engine/Window.h"

// Game Scenes
#include "Scenes/Credits.h"
#include "Scenes/Menu.h"
#include "Scenes/Gameplay.h"

class Game
{
private:
    int running;
    char* name;

    // Scenes
    enum Scenes{CREDITS, MENU, GAME}; // Enum for easy access
    Scenes sceneName;
    Scene* scene;
    Window* window;

public:
    Game(char*, int);
    ~Game();
    int ChangeScene(Scenes);
    int IsRunning();
    int OnInit();
    void OnCall();
};

#endif