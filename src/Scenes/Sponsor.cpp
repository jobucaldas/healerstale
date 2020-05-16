#include "Scenes/Sponsor.h"

Sponsor::Sponsor()
{

}

Sponsor::~Sponsor()
{
    delete sponsorImg;
}

int Sponsor::OnCall(SDL_Renderer* renderer)
{
    Render(renderer);
    return 0;
}

int Sponsor::Render(SDL_Renderer* renderer)
{
    sponsorImg->Render(renderer);

    return 0;
}

void Sponsor::Loading(SDL_Renderer* renderer, SDL_Rect screenRect)
{
    LoadGUI(renderer, screenRect);
    loaded = 1;
}

void Sponsor::LoadGUI(SDL_Renderer* renderer, SDL_Rect screenRect)
{
    std::string sponsorPath = "Assets/Sprites/UI/Sponsor.png";
    // Set sponsor img
    #ifdef __vita__
        sponsorPath = "app0:/" + sponsorPath;
    #endif

    sponsorImg = new GUIElement(sponsorPath.c_str(), renderer);

    if(sponsorImg == NULL)
    {
        printf("Problem loading image.\n");
    } else
    {
        sponsorImg->SetSize(screenRect.h * 0.8, screenRect.h * 0.8);
        sponsorImg->SetPosition(screenRect.w/2 - sponsorImg->GetRect().w/2, screenRect.h/2 - sponsorImg->GetRect().h*0.45);
        printf("Set rect and pos.\n");
    }

    
}