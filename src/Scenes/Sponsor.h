#ifndef SPONSOR_H
#define SPONSOR_H

#include "Engine/Scene.h"

#include "Engine/GUIElement.h"

class Sponsor : public Scene
{
public:
    Sponsor();
    ~Sponsor();
    void Loading(SDL_Renderer*, SDL_Rect);
    void LoadGUI(SDL_Renderer*, SDL_Rect);
    int Render(SDL_Renderer*);
    int OnCall(SDL_Renderer*);

private:
    GUIElement* sponsorImg;
};

#endif