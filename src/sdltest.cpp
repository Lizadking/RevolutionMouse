#include <iostream>
#include <stdio.h>
#include <SDL.h>

int main()
{
    int initSDLVideo = SDL_Init(SDL_INIT_VIDEO);
    if(initSDLVideo < 0)
    { 
        std::cout<<" Failed to init SLD video "<<std::endl;
        return -1;
    }
    std::cout<<"SDL VIDEO INIT DONE"<<std::endl;

    int initSDLEvent = SDL_Init(SDL_INIT_EVENTS);
    if(initSDLEvent < 0)
    {
        std::cout<<"Failed to init SLD Events"<<std::endl;
        return -1;
    }
    std::cout<<"SDL EVENT INIT DONE"<<std::endl;

    /*-----------Video subsystem----------------*/
    // Get information about the displays and other misc information 
    SDL_DisplayMode SDL_display;
    SDL_Rect SDL_rect;
    int numberOfDisplays = SDL_GetNumVideoDisplays();
    int numberOfVideoDrivers =  SDL_GetNumVideoDrivers();
    const char * videoDriver = SDL_GetVideoDriver(0); /*index of the video driver This also gets the display protocol */
    int displayModeCheck =  SDL_GetCurrentDisplayMode(0,&SDL_display);
    int displayBounds = SDL_GetDisplayBounds(0,&SDL_rect);

    
    if(displayModeCheck != 0)
    {
        std::cout<<"Error on bounds check"<<std::endl;
    }


    std::cout<<"---Monitor Report---"<<std::endl;
    printf("Number of Displays:\t %d\n",numberOfDisplays);
    printf("Video Driver: \t %s\n",videoDriver);
    printf("Video Driver Count: \t %d\n",numberOfVideoDrivers);
    printf("Display Rect W:\t %dpx\n",SDL_display.w);
    printf("Display Rect h:\t %dpx\n",SDL_display.h);
    printf("Display Bounds:\t %dpx\n",displayBounds);

    std::cout<<"---Mouse Report---"<<std::endl;
    /*-----------Mouse subsystem----------------*/
    for(int i = 0; i< 2000;i++)
    {
        SDL_WarpMouseGlobal(i,300); // WOW THIS IS FAST AND WORKS WITHOUT LIBEV DEV !! IT'S PROBABLY CROSS  PLATFORM TOO Maybe it can be the main way to move the mouse


    }

    while(true)
    {
        SDL_Keycode keycode;
        SDL_Scancode scancode;
        scancode = SDL_GetScancodeFromKey(keycode);
        std::cout<<scancode<<std::endl;
    }
    
    
    
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
    SDL_QuitSubSystem(SDL_INIT_EVENTS);
    return 0;
}