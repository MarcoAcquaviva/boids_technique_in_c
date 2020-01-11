#include "draw.h"
#include "engine.h"

SDL_Texture *SetTexture(SDL_Renderer *renderer, const char *filename)
{

    //IMPORT PNG
    int width, height, comp;
    unsigned char *image = stbi_load(filename, &width, &height, &comp, STBI_rgb_alpha); /// zero or four result's is equal
    if (!image)
    {
        die("Unable to load image");
    }

    //CREATE A TEXTURE FOR GPU
    SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32 , SDL_TEXTUREACCESS_STREAMING, width, height);
    if (!texture)
    {
        die("Unable to create texture");
    }
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

    //MAP TEXTURE INTO ADDRESS SPACE
    Uint8 *pixels = NULL;
    int pitch = 0;
    if (SDL_LockTexture(texture, NULL, (void **)&pixels, &pitch))
    {
        die("Unable to map texture into address space");
    }

    SDL_Log("Texture mapped at %p with ptich %d", pixels, pitch);
    memcpy(pixels, image, pitch * height); //COPY IMAGE INTO STACK
    free(image);                           //Free HEAP
    SDL_UnlockTexture(texture);

    return texture;
}

void Draw(SDL_Renderer *renderer, SDL_Texture *t, SDL_Rect rect, float x, float y,float rotation)
{

    int w, h;

    if (SDL_QueryTexture(t, NULL, NULL, &w, &h))
    {
        die("Unable to queue texture");
    }

    //Create the area where to render

    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    //printf("Width: %d \n Height: %d\n", w, h);

    //Copy from Ram to address area
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    SDL_RenderCopyEx(renderer, t, NULL, &rect,rotation,NULL,flip);
}


