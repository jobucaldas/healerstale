#ifndef WINDOW_H
#define WINDOW_H

// Structures
#include "Engine/Structures.h"

// SDL
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

// Canvas
#include "Engine/Scene.h"
#include "Scenes/Credits.h"
#include "Scenes/Sponsor.h"
#include "Scenes/Menu.h"

class Window
{
public:
    /* Variables */
    // Events
    SDL_Event events;
    int running;

    // Window
    SDL_Window* window;
    SDL_Surface* screenSurface;
    SDL_Renderer* renderer;
    SDL_DisplayMode displayMode;


    // Canvas
    Scene* scene;

    /* Functions */
    // Construct
    Window(char*, int);
    ~Window();

    // Getters
    int IsRunning();

    // Call
    int OnCall();

    // Actions
    void EventHandler();
    int ChangeScene(SceneType);

private:
    Uint32 displayFlags; 
    SDL_Rect displayRect;
};

#endif