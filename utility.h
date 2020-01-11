#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#ifndef UTILITY_H
#define UTILITY_H

typedef struct Vector2
{
    float x;
    float y;
}Vector2_t;

__declspec(selectany) Vector2_t origin = {.x=0, .y= 0};


// I from 0 to N
int int_parse(const char *value);

//  I from N to 0
int int_parse_decrement_I(const char *value);

int print(const char *message);

uint8_t random_uint8(uint8_t max);

int dot_product(int *, int *, size_t);

Vector2_t vector2_addiction(Vector2_t a, Vector2_t b);

Vector2_t vector2_subtraction(Vector2_t a,Vector2_t b);

Vector2_t vector2_division_by_value(Vector2_t a, float value);

Vector2_t vector2_multiply_with_value(Vector2_t a, float value);

Vector2_t vector2_normilized(Vector2_t a);

float lerp(float start, float end, float gradient);

Vector2_t vector2_lerp(Vector2_t a, Vector2_t b, float fraction);

void vector2_normilize(Vector2_t *a);

float vector2_get_length(Vector2_t a, Vector2_t b);

void print_vector2(Vector2_t *v);

#endif