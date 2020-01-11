#include <SDL.h>
#include "GUI.h"
#include "utility.h"

#ifndef BOIDS_H
#define BOIDS_H

typedef struct boid
{
    Vector2_t position;
    Vector2_t direction;
    float speed;
    float alignment_radius;
    float cohesion_radius;
    float separation_radius;

    float alignment_weight;
    float cohesion_weight;
    float separation_weight;

    gui_t *gui_obj;
}boid_t;

typedef struct boid_list{
    boid_t *boids;
    int nboids;
}boid_list_t;

__declspec(selectany) const char *boid_texture_name = "img/arrow.png";

void initBoid(boid_t *boid_obj, Vector2_t pos,Vector2_t dir, const char *filename);

void update_boid(boid_t *boid_obj, boid_list_t *boids, int index);

void drawBoid(boid_t *boid_obj);

float IsVisible(boid_t *my_boid_obj,boid_t *boid_obj, int type);

Vector2_t GetAlignment(boid_list_t *boids, int index);

Vector2_t GetCohesion(boid_list_t *boids, int index);

Vector2_t GetSeparetion(boid_list_t *boids, int index);

boid_list_t* init_boid_list();

void add_boid_to_list(boid_list_t *boids,Vector2_t pos);

void update_boids(boid_list_t *boids);

void draw_boids(boid_list_t *boids);

#endif