#include <SDL.h>

#ifndef GUI_H
#define GUI_H
typedef struct gui
{
    float x;
    float y;
    SDL_Texture *texture;
    SDL_Rect rect;
}gui_t;


void initGUI(gui_t *gui_obj, const char *filename, float x, float y);

void drawGUI(gui_t *gui_obj,float rotation);

#endif