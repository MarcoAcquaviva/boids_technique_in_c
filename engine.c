#include "engine.h"

//INIT DRIVER
int init_driver(uint32_t flags){
    if (SDL_Init(flags))
    {
       die("Error initializing SLD 2");
    }
    printf("Init Driver\n");
    return 0;
}


//INIT WINDOW
int init_window(window_t win)
{
    const char *name = win.name;
    int x = win.x;
    int y = win.y;
    int w = win.w;
    int h = w / 4 * 3;
    uint32_t flags = win.flags;

    G_window = SDL_CreateWindow(name, x,y, w,h, flags);
    if (!G_window)
    {
      die("Error creating window:");
    }

    printf("Init Window\n");
    return 0;
}


//RENDER WIDNOW OPTIONS
int init_renderer(SDL_Window *window, uint32_t flags)
{
    G_renderer = SDL_CreateRenderer(window, -1, flags);
    if (!G_renderer)
    {
        die("Error: ");
    }

    printf("Init Renderer\n");
    return 0;
}


int die(const char *message){
    SDL_Log("%s: %s", message, SDL_GetError());
    SDL_Quit();
    return 1;
}

int error(const char *message)
{
    printf("%s \n", message);
    SDL_Quit();
    return 1;
}

int end(){
    SDL_DestroyWindow(G_window );
    SDL_DestroyRenderer(G_renderer);
    SDL_Quit();
    return 0;
}