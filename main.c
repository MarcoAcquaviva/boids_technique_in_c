#define SDL_MAIN_HANDLED
#define STB_IMAGE_IMPLEMENTATION

#include <string.h>
#include "classes.h"

int main(int argc, char **argv)
{
    printf("Start Application\n");

    //VARIABLE
    SDL_Event event;
    NOW = SDL_GetPerformanceCounter();

    //ENGINE
    init_driver(SDL_INIT_EVERYTHING);

    window.name = "Boids";
    window.x = 100;
    window.y = 100;
    window.w = 800;
    window.h = window.w / 4 * 3;
    window.flags = SDL_WINDOW_SHOWN;
    init_window(window);
    init_renderer(G_window, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

    //Vector2_t pos = {.x = 100, .y = 100};
    //Vector2_t dir = {.x = 1, .y = -1};

    // boid_t b;
    //initBoid(&b,pos,dir,boid_texture_name);

    boid_list_t *boids = init_boid_list();

    //GAMELOOP
    for (;;)
    {

        LAST = NOW;
        NOW = SDL_GetPerformanceCounter();
        deltaTime = (double)((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency());

        int mouseX, mouseY;
        float mouse_click_wait = 1.5f;
        float mouse_timer;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                return end();
            }

            if (SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
                if (mouse_click_wait < mouse_timer)
                {
                    mouse_timer = 0;
                    Vector2_t pos = {.x = mouseX, .y = mouseY};
                    add_boid_to_list(boids, pos);
                }
            }
            else
            {
                mouse_timer += deltaTime;
            }
        }

        //UPDATE
        // update_boid(&b);
        update_boids(boids);

        //CLEAN SCREEN
        SDL_SetRenderDrawColor(G_renderer, 113, 202, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(G_renderer);

        //DRAW
        // drawBoid(&b);
        draw_boids(boids);

        //SHOW SCREEN
        SDL_RenderPresent(G_renderer);
    }

    return end();
}