#ifndef PHYSICS_H   /* header guard */
#define PHYSICS_H


typedef struct {
    float x;
    float y;
} Vector2;


typedef struct {
    Vector2 position;
    Vector2 velocity;
    Vector2 accelaration;
    char symbol[3];
} Point;


void handle_and_draw_particles(Point particles[], unsigned size);


#endif