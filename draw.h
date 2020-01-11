#include <SDL.h>
#include "stb_image.h"
#include <string.h>



SDL_Texture* SetTexture(SDL_Renderer *renderer,const char *filename);

void Draw(SDL_Renderer *renderer,SDL_Texture* t, SDL_Rect rect, float x, float y,float rotation);
