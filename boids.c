#include "boids.h"
#include "engine.h"
#define PI 3.141592654

static void update_GUI_position(boid_t *boid_obj)
{
    float x = boid_obj->position.x;
    float y = boid_obj->position.y;
    boid_obj->gui_obj->x = x;
    boid_obj->gui_obj->y = y;
}

void initBoid(boid_t *boid_obj, Vector2_t pos, Vector2_t dir, const char *filename)
{

    //Set pos
    boid_obj->position = pos;
    boid_obj->direction = dir;
    boid_obj->speed = 10.0f;
    boid_obj->alignment_radius = 150.0f;
    boid_obj->cohesion_radius = 100.0f;
    boid_obj->separation_radius=70.0f;
    boid_obj->alignment_weight = 0.5f;
    boid_obj->cohesion_weight = 0.2f;
    boid_obj->separation_weight = 0.9f;

    //Set texture
    gui_t *g = malloc(sizeof(gui_t));
    initGUI(g, filename, pos.x, pos.y);
    boid_obj->gui_obj = g;
    print_vector2(&boid_obj->position);
}

void update_boid(boid_t *boid_obj, boid_list_t *boids, int index)
{
    float speed = boid_obj->speed;
    Vector2_t *my_velocity = &boid_obj->direction;

    //GET FACTORS
    Vector2_t alignmnet = vector2_multiply_with_value(GetAlignment(boids,index),boid_obj->alignment_weight);
    Vector2_t cohesion = vector2_multiply_with_value(GetCohesion(boids,index),boid_obj->cohesion_weight);
    Vector2_t separation =vector2_multiply_with_value( GetSeparetion(boids,index),boid_obj->separation_weight);

    //SUM THE FACTORS TO GET A NEW VECTOR
    Vector2_t sum_of_factors;
    sum_of_factors.x = alignmnet.x + cohesion.x + separation.x;
    sum_of_factors.y = alignmnet.y + cohesion.y + separation.y;

    //CHECK IF THE RESULT IS A VALID VALUE
    if(sum_of_factors.x != 0 && sum_of_factors.y != 0)
    {
        sum_of_factors = vector2_normilized(sum_of_factors);
        *my_velocity = vector2_lerp(*my_velocity,vector2_multiply_with_value(sum_of_factors,speed),deltaTime/1000);
        *my_velocity = vector2_multiply_with_value(vector2_normilized(*my_velocity),speed);
    }


    //UPDATE POSITION
    Vector2_t dir_fraction = vector2_multiply_with_value(boid_obj->direction, deltaTime/1000);
    Vector2_t dir_per_speed = vector2_multiply_with_value(dir_fraction,speed);
    Vector2_t *pos = &boid_obj->position;
    *pos = vector2_addiction(boid_obj->position, dir_per_speed);

    //BOUNDARY
    float x = pos->x;
    float y = pos->y;

    if (x > window.w)
        pos->x = 0;
    else if (x < 0)
        pos->x = window.w;

    if (y > window.h)
        pos->y = 0;
    else if (y < 0)
        pos->y = window.h;

    //UPDATE GUI
    update_GUI_position(boid_obj);

    //PRINTs
    //printf("%f\n",speed);
    //print_vector2(&alignmnet);
}

void drawBoid(boid_t *boid_obj)
{
    float rotation = atan2(boid_obj->direction.y,boid_obj->direction.x)*180/PI;
    drawGUI(boid_obj->gui_obj,rotation);


    //PRINTS
    //printf("rotation= %f\n",rotation);
}

float IsVisible(boid_t *my_boid_obj,boid_t *boid_obj, int type)
{
    float_t radius;

    switch (type)
    {
    case 1:
        radius = my_boid_obj->alignment_radius;
        break;
   case 2:
        radius = my_boid_obj->cohesion_radius;
        break;
           case 3:
        radius = my_boid_obj->separation_radius;
        break;
    }


    Vector2_t my_pos = my_boid_obj->position;
    Vector2_t other_pos = boid_obj->position;
    Vector2_t direction = vector2_subtraction(my_pos,other_pos);
    float distance = vector2_get_length(my_pos,other_pos);

    if(radius >= distance){
        return 1;
    }

    return 0;
}

Vector2_t GetAlignment(boid_list_t *boids, int index)
{
    int nboids = boids->nboids;
    int count = 0;
    Vector2_t sum_velocity= {.x = 0,.y= 0};
    float *speed;

    for (size_t i = 0; i < nboids; i++)
    {
        if(i != index)
        {
            boid_t *my_boid = &boids->boids[index];
            boid_t *other_boid = &boids->boids[i];
            speed = &my_boid->speed;
            if(IsVisible(my_boid,other_boid, 1))
            {
                Vector2_t other_velocity = other_boid->direction;
                sum_velocity = vector2_addiction(sum_velocity,other_velocity );
                count++;
            }           
        }
    }

    if(count >0 )
    {
        sum_velocity = vector2_division_by_value(sum_velocity,count);
        if(vector2_get_length(origin, sum_velocity) != 0){
            sum_velocity = vector2_multiply_with_value( vector2_normilized(sum_velocity), *speed);            
        }
    }

    return sum_velocity;

}

Vector2_t GetCohesion(boid_list_t *boids, int index)
{
    int nboids = boids->nboids;
        int count = 0;
    Vector2_t sum_velocity= {.x = 0,.y= 0};
    float *speed;
    Vector2_t *my_pos;

    for (size_t i = 0; i < nboids; i++)
    {
        if(i != index)
        {
            boid_t *my_boid = &boids->boids[index];
            boid_t *other_boid = &boids->boids[i];
            speed = &my_boid->speed;
            my_pos = &my_boid->position;
            if(IsVisible(my_boid,other_boid,2))
            {
                Vector2_t other_velocity = other_boid->direction;
                sum_velocity = vector2_addiction(sum_velocity,other_velocity );
                count++;
            }
            
        }
    }

    if(count >0)
    {
        sum_velocity = vector2_division_by_value(sum_velocity,count);

        Vector2_t distToCenter = vector2_subtraction(sum_velocity,*my_pos);

        sum_velocity = vector2_multiply_with_value(vector2_normilized(distToCenter),*speed);
    }

    return sum_velocity;

}

Vector2_t GetSeparetion(boid_list_t *boids, int index)
{
    int nboids = boids->nboids;
        int count = 0;
    Vector2_t sum_velocity= {.x = 0,.y= 0};
    float *speed;

    for (size_t i = 0; i < nboids; i++)
    {
        if(i != index)
        {
            boid_t *my_boid = &boids->boids[index];
            boid_t *other_boid = &boids->boids[i];
            speed = &my_boid->speed;
            if(IsVisible(my_boid,other_boid,3))
            {
                Vector2_t other_velocity = other_boid->direction;
                sum_velocity = vector2_addiction(sum_velocity,other_velocity );
                count++;
            }
            
        }
    }

    if(count >0)
    {
        sum_velocity = vector2_division_by_value(sum_velocity,count);
        sum_velocity = vector2_multiply_with_value(vector2_normilized(sum_velocity),-*speed);
    }

    return sum_velocity;

}

//BOID LIST

boid_list_t *init_boid_list()
{
    boid_list_t *boids = malloc(sizeof(boid_list_t));
    memset(boids, 0, sizeof(boid_list_t));
    boids->boids = NULL;
    return boids;
}

void add_boid_to_list(boid_list_t *boids, Vector2_t pos)
{

    boid_t *new_boids = realloc(boids->boids, sizeof(boid_t) * (boids->nboids + 1));
    boids->boids = new_boids;


    int randomX = rand() % (50 + 1 - -50) + -50;
      int randomY = rand() % (50 + 1 - -50) + -50;
    
    Vector2_t dir = {.x = randomX, .y = randomY};
    boid_t b;
    initBoid(&b, pos, dir, boid_texture_name);
    boids->boids[boids->nboids].direction = b.direction;
    boids->boids[boids->nboids].gui_obj = b.gui_obj;
    boids->boids[boids->nboids].position = b.position;
    boids->boids[boids->nboids].speed = b.speed;
    boids->boids[boids->nboids].alignment_radius = b.alignment_radius;
    boids->boids[boids->nboids].cohesion_radius = b.cohesion_radius;
    boids->boids[boids->nboids].separation_radius = b.separation_radius;
    boids->boids[boids->nboids].alignment_weight = b.alignment_weight;
    boids->boids[boids->nboids].cohesion_weight = b.cohesion_weight;
    boids->boids[boids->nboids].separation_weight = b.separation_weight;

    boids->nboids++;

    //PRINTs
    //printf("nboids: %d\n", boids->nboids);
}

void update_boids(boid_list_t *boids)
{
    int nboids = boids->nboids;

    for (size_t i = 0; i < nboids; i++)
    {
        update_boid(&boids->boids[i],boids,i);
    }
}

void draw_boids(boid_list_t *boids)
{

    int nboids = boids->nboids;

    for (size_t i = 0; i < nboids; i++)
    {
        drawBoid(&boids->boids[i]);
    }
}