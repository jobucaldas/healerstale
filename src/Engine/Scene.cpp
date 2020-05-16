#include "Engine/Scene.h"

Scene::Scene()
{
    loaded = 0;
    finished = 0;
    nextScene = MENU;
}

Scene::~Scene()
{

}

int Scene::Render(SDL_Renderer* renderer)
{
    return 0;
}

void Scene::OnEvent(SDL_Event event)
{

}

int Scene::OnCall(SDL_Renderer* renderer)
{
    Render(renderer);
    return 0;
}

int Scene::IsLoaded()
{
    return loaded;
}

void Scene::Loading(SDL_Renderer* renderer, SDL_Rect screenRect)
{
    LoadGUI(renderer, screenRect);

    // Set to loaded (so that it only loads once)
    loaded = 1;
}

void Scene::SetNextScene(SceneType type)
{
    nextScene = type;
}

void Scene::LoadGUI(SDL_Renderer* renderer, SDL_Rect screenRect)
{
    
}

int Scene::IsFinished()
{
    return finished;
}

int Scene::UnloadedGUI()
{
    return guiElements;
}

SceneType Scene::GetNextScene()
{
    return nextScene;
}