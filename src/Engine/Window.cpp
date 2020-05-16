#include "Engine/Window.h"

Window::Window(char* gameName, int fullscreen)  // Name on window header and if fullscreen is expected
{
    // Make window object
    window = NULL;
    screenSurface = NULL;
    running = 1;

    // Declare display mode structure to be filled in.
    displayRect.h = 720;
    displayRect.w = 1280;
    displayFlags = SDL_WINDOW_SHOWN; 


    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        running = 0;
    } else
    {
        SDL_GetCurrentDisplayMode(0, &displayMode); 

        #ifdef __vita__
            displayRect.h = 544;
            displayRect.w = 960;

            window = SDL_CreateWindow( gameName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, displayRect.w, displayRect.h, SDL_WINDOW_SHOWN);

            screenSurface = SDL_GetWindowSurface(window);

            renderer = SDL_CreateRenderer( window, -1, 0);
        #else
            //Create window
            if(fullscreen)
            {
                displayRect.h = displayMode.h;
                displayRect.w = displayMode.w;
                displayFlags = (SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);            
            }

            window = SDL_CreateWindow(gameName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, displayRect.w, displayRect.h, displayFlags);

            if( window == NULL )
            {
                printf( "Failed to create window.\nError: %s\n", SDL_GetError() );
                running = 0;
            } else
            {            
                //Get window surface
                screenSurface = SDL_GetWindowSurface(window);

                renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

                if(renderer == NULL)
                {
                    printf( "Failed to create renderer.\nSDL Error: %s\n", SDL_GetError() );
                    running = 0;
                } else
                {
                    //Initialize renderer color
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
                }
            }
        #endif

        // On startup, show sponsor screen (should load menu afterwards automatically)
        ChangeScene(SPONSOR);
    }

    if(running) printf("Window created without problems.\n");
}

Window::~Window()
{
    // Delete current scene
    delete scene;

    //Deallocate surface
    SDL_FreeSurface(screenSurface);
    screenSurface = NULL;

    // Destroy things loaded
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    // Quit SDL
    IMG_Quit();
    SDL_Quit();
}

void Window::EventHandler()
{
    // Events that should work everywhere
    while (SDL_PollEvent(&events))
    {
        if (events.type == SDL_QUIT)
        {
            running = 0;
        } else // Send events related to scene only
        {
            scene->OnEvent(events);
        }
    }
}

int Window::ChangeScene(SceneType sceneType)
{
    char* sceneName;

    if(sceneType == CREDITS)
    {
        scene = new Credits();
        sceneName = "Credits";
    } else if(sceneType == SPONSOR)
    {
        scene = new Sponsor();
        sceneName = "Sponsor";
    } else if(sceneType == MENU)
    {
        scene = new Menu();
        sceneName = "Menu";
    } else
    {
        scene = new Scene();
        sceneName = "No Scene";
    }

    printf("Scene: %s\n", sceneName);

    return 0;
}

int Window::OnCall()
{
    EventHandler();

    //Clear screen
    SDL_RenderClear( renderer );

    if(!scene->IsLoaded())
    {
        scene->Loading(renderer, displayRect);
    }

    scene->OnCall(renderer);

    if(scene->IsFinished())
    {
        ChangeScene(scene->GetNextScene());
    }

    //Update screen
    SDL_RenderPresent(renderer);

    return running;
}

int Window::IsRunning()
{
    return running;
}