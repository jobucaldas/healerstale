#ifdef __vita__
    #include <psp2/kernel/processmgr.h>
#endif
#include "Engine/Window.h"

int main(int argc, char* argv[])
{
    char* gameName = "Healer's Tale"; // Change acordingly

    int fullscreen = 0;

    for (int i = 0; i < argc; i++)
        if(strcmp(argv[i], "--fullscreen") || strcmp(argv[i], "-f")) fullscreen = 1;
    
    Window* window = new Window(gameName, fullscreen); // Set fullscreen or not

    while(window->OnCall()){}

    delete window;

#ifdef __vita__
    sceKernelExitProcess(0);
#endif

    return 0;
}