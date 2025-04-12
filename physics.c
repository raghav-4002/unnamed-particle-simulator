#include "physics.h"
#include "draw.h"
#include "setup.h"


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
        // point->accelaration.x *= -0.1;
        point->velocity.x     *= -1;
    }

    if(point->position.y >= term_attributes.screen_length || point->position.y <= 0) {
        // point->accelaration.y *= -0.1;
        point->velocity.y     *= -1;
    }
}


void
update_position(Point *point)
{
    point->position.x += point->velocity.x;
    point->position.y += point->velocity.y;
}


void
update_velocity(Point *point1, Point *point2)
{

}


void
update_parameters(Point *point)
{
    // point->velocity.x += point->accelaration.x;
    // point->velocity.y += point->accelaration.y;

    point->position.x += point->velocity.x;
    point->position.y += point->velocity.y;
}


void
detect_collision(Point particles[], unsigned particle_count)
{
    for(unsigned i = 0; i < particle_count; i++) {
        for(unsigned j = i + 1; j < particle_count; j++) {
            if(particles[i].position.x == particles[j].position.x &&
                particles[i].position.y == particles[j].position.y) {
                
                // do something
            }
        }
        rebound_from_edges(&particles[i]);
        update_position(&particles[i]);
        draw(&particles[i]);
    }
}