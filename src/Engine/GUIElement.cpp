#include "Engine/GUIElement.h"

GUIElement::GUIElement(std::string path, SDL_Renderer* renderer)
{
    LoadTexture(path, renderer);
}

GUIElement::~GUIElement()
{
    SDL_DestroyTexture(texture);
}

void GUIElement::Render(SDL_Renderer* renderer)
{
    if(&rectDestination == NULL)
    {
        printf("Rect not set.\n");
    } else{
        SDL_RenderCopy(renderer, texture, NULL, &rectDestination);
    }
}

int GUIElement::LoadTexture(std::string path, SDL_Renderer* renderer)
{
    //The final texture
    texture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if( loadedSurface == NULL )
    {
        printf("Failed to load image %s.\nSDL_image Error: %s\n", path, IMG_GetError());
        return 1;
    }
    else
    {
        //Create texture from surface pixels
        texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if( texture == NULL )
        {
            printf( "Failed to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
            return 1;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    printf("Image loaded correctly.\n");
    return 0;
}

void GUIElement::Move(double posx, double posy)
{
    rectDestination.x += posx;
    rectDestination.y += posy;
}

void GUIElement::SetPosition(double posx, double posy)
{
    rectDestination.x = posx;
    rectDestination.y = posy;
}

SDL_Rect GUIElement::GetRect()
{
    return rectDestination;
}

void GUIElement::SetSize(double sizex, double sizey)
{
    rectDestination.h = sizex;
    rectDestination.w = sizey;
}
