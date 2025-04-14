#include "physics.h"
#include "draw.h"
#include "setup.h"


void
update_position(Point *point)
{
    point->position.x += point->velocity.x;
    point->position.y += point->velocity.y;
}



void
rebound_from_edges(Point *point)
{
    if(point->position.x >= term_attributes.screen_width || point->position.x <= 0) {
        point->velocity.x *= -1;
    }

    if(point->position.y >= term_attributes.screen_length || point->position.y <= 0) {
        point->velocity.y *= -1;
    }
}


void
handle_particles(Point particles[], unsigned particle_count)
{
    for(unsigned i = 0; i < particle_count; i++) {
        draw_particle(&particles[i]);
        rebound_from_edges(&particles[i]);
        update_position(&particles[i]);
    }       
}