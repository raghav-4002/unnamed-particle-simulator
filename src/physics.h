#ifndef PHYSICS_H   /* header guard */
#define PHYSICS_H


/* struct to represent a 2D vector */
typedef struct {
    float x;
    float y;
} Vector2;

/* struct to represent a point on screen */
typedef struct {
    Vector2 position;
    Vector2 current_velocity;
    Vector2 prev_velocity;
    char symbol[3];
} Point;


void handle_and_draw_particles(Point particle[], unsigned size);


#endif