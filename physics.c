#include "physics.h"


void
apply_force(Point *point, Vector2 force)
{
    point->accelaration.x = (force.x / point->mass);
    point->accelaration.y = (force.y / point->mass);
}