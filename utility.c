#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "utility.h"

// I from 0 to N
int int_parse(const char *value)
{
    int accumulator = 0;
    int places = strlen(value);
    for (int i = 0; i <= places - 1; i++)
    {
        //i = 2
        //i = 1
        //i = 0
        int n = value[places - 1 - i] - '0';
        accumulator += n * pow(10, i);
    }
    return accumulator;
}

//  I from N to 0
int int_parse_decrement_I(const char *value)
{
    int accumulator = 0;
    int places = strlen(value);
    for (int i = places - 1; i >= 0; i--)
    {
        //i = 2
        //i = 1
        //i = 0
        int n = value[places - 1 - i] - '0';
        accumulator += n * pow(10, i);
    }
    return accumulator;
}

int print(const char *message)
{
    return printf("%s \n", message);
}

uint8_t random_uint8(uint8_t max)
{
    return rand() % max;
}

int dot_product(int *a, int *b, size_t n)
{
    int sum = 0;
    size_t i;

    for (i = 0; i < n; i++)
    {
        sum += a[i] * b[i];
    }

    return sum;
}

Vector2_t vector2_addiction(Vector2_t a, Vector2_t b)
{
    Vector2_t vv;
    vv.x = a.x + b.x;
    vv.y = a.y + b.y;
    return vv;
}

// Operation is B - A 
Vector2_t vector2_subtraction(Vector2_t a, Vector2_t b)
{
    Vector2_t vv;
    vv.x = b.x-a.x;
    vv.y = b.y-a.y;
    return vv;
}

Vector2_t vector2_division_by_value(Vector2_t a, float value){
    Vector2_t vv = {.x= -1, .y =-1};
    if(value != 0)
    {
    vv.x = a.x/value;
    vv.y = a.y/value;    
    }
    return vv;
}


Vector2_t vector2_multiply_with_value(Vector2_t a, float value)
{
    Vector2_t vv;
    vv.x = a.x * value;
    vv.y = a.y * value;
    return vv;
}

Vector2_t vector2_normilized(Vector2_t a)
{
    Vector2_t vv = {.x= -1,.y= -1};
    float length = vector2_get_length(origin,a);
    if(length >0)
    {
        vv = vector2_division_by_value(a,length);
        return vv;
    }

    return vv;
}


float lerp(float start, float end, float gradient)
{
    return start + (end - start) * gradient;
}

Vector2_t vector2_lerp(Vector2_t a, Vector2_t b, float fraction){
    Vector2_t vv;
    vv.x = lerp(a.x, b.x, fraction);
    vv.y = lerp(a.y, b.y, fraction);
    return vv;
}

void vector2_normilize(Vector2_t *a){
    float length = vector2_get_length(origin,*a);
    if(length >0)
    {
        *a = vector2_division_by_value(*a,length);
    }
}

// B - A
float vector2_get_length(Vector2_t a, Vector2_t b){
    float length;
    float powX = pow((b.x - a.x),2);
    float powY = pow((b.y - a.y),2);
    length = sqrt((powX+powY));
    if(length >0)
    return length;
    else
    return -1;
}

void print_vector2(Vector2_t *v){
    float x = v->x;
    float y = v->y;
    printf("X: %f, Y: %f\n",x,y);
}