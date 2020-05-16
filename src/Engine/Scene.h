#ifndef SCENE_H
#define SCENE_H

// C++
#include <iostream>

// Structures
#include "Engine/Structures.h"

// SDL
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

class Scene
{
public:
    Scene();
    ~Scene();
    virtual int Render(SDL_Renderer*);
    virtual void OnEvent(SDL_Event);
    virtual int OnCall(SDL_Renderer*);
    SDL_Texture* MakeTexture(char*);

    int IsLoaded();
    virtual void Loading(SDL_Renderer*, SDL_Rect);

    // Scene related
    int IsFinished();
    SceneType GetNextScene();

    // GUI
    int UnloadedGUI();
    void LoadGUI(SDL_Renderer*, SDL_Rect);

    SDL_Texture* LoadTexture(char*, SDL_Renderer*);

protected:
    int finished;
    int loaded;

private:
    // Scene related    
    SceneType nextScene;
    void SetNextScene(SceneType);

    // GUI
    int guiElements;
};

#endif