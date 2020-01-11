#include "GUI.h"
#include "draw.h"
#include "engine.h"

void initGUI(gui_t *gui_obj, const char *filename, float x, float y){
    gui_obj -> x = x;
    gui_obj -> y = y;
    gui_obj -> texture = SetTexture(G_renderer, filename);
}

void drawGUI(gui_t *gui_obj, float rotation){

    float x = gui_obj->x;
    float y = gui_obj->y;
    SDL_Texture *texture = gui_obj -> texture;
    SDL_Rect rect = gui_obj -> rect;

    Draw(G_renderer,texture,rect,x,y,rotation);
}