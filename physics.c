#include "physics.h"
#include "basic.h"


void
apply_force(Point *point, Vector2 force)
{
    point->accelaration.x = (force.x / point->mass);
    point->accelaration.y = (force.y / point->mass);
}


void
rebound_from_edges(Point *point)
{
    if(point->position.x >= term_attributes.screen_width || point->position.x <= 0) {
        point->accelaration.x *= -0.1;
        point->velocity.x     *= -1;
    }

    if(point->position.y >= term_attributes.screen_length || point->position.y <= 0) {
        point->accelaration.y *= -0.1;
        point->velocity.y     *= -1;
    }
}