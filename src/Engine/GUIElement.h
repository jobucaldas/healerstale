#ifndef GUIELEMENT_H
#define GUIELEMENT_H

#include <string>

// SDL
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

class GUIElement
{
public:
    GUIElement(std::string, SDL_Renderer*);
    ~GUIElement();

    void SetSize(double, double);
    int LoadTexture(std::string, SDL_Renderer*);
    void SetPosition(double, double);
    void Render(SDL_Renderer*);
    void Move(double, double);
    SDL_Rect GetRect();


private:
    SDL_Rect rectDestination;
    SDL_Texture* texture;
};

#endif