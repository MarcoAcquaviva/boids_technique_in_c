#include <SDL.h>
#include <stdio.h>

typedef struct window
{
    int x,y,w,h;
    char *name;
    uint32_t flags;
}window_t;

window_t window;
SDL_Window *G_window;
SDL_Renderer *G_renderer;

Uint64 NOW;
Uint64 LAST;
double deltaTime;

//INIT DRIVER
int init_driver(uint32_t flags);


//INIT WINDOW
int init_window(window_t win);


//RENDER WIDNOW OPTIONS
int init_renderer(SDL_Window *window, uint32_t flags);


int die(const char *message);

int error(const char *message);

int end();