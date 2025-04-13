#ifndef PHYSICS_H   /* header guard */
#define PHYSICS_H


typedef struct {
    float x;
    float y;
} Vector2;

typedef float Some_mass_unit_idk;

typedef struct {
    Some_mass_unit_idk mass;
    Vector2 position;
    Vector2 velocity;
    Vector2 accelaration;
    char symbol[3];
} Point;


void update_parameters(Point particles[], unsigned size);


#endif