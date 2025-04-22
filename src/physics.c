#include "physics.h"
#include "draw.h"
#include "setup.h"


void
update_position(Point *point)
{
    point->position.x += point->current_velocity.x;
    point->position.y += point->current_velocity.y;
}



void
rebound_from_edges(Point *point)
{
    if(point->position.x >= term_attributes.screen_width || point->position.x <= 0) {
        point->current_velocity.x *= -1;
    }

    if(point->position.y >= term_attributes.screen_length || point->position.y <= 0) {
        point->current_velocity.y *= -1;
    }
}


void
handle_collision(Point particle1, Point particle2)
{
    // do something
}


void
handle_and_draw_particles(Point particles[], unsigned particle_count)
{
    unsigned i, j;

    for(i = 0; i < particle_count; i++) {
        draw_particle(&particles[i]);
        rebound_from_edges(&particles[i]);
        update_position(&particles[i]);
    }       

    for(i = 0; i < particle_count - 1; i++) {
        for(j = i + 1; j < particle_count; j++) {
            if(particles[i].position.x == particles[j].position.x && 
               particles[i].position.y == particles[j].position.y) {
                handle_collision(particles[i], particles[j]);
            }
        }
    }
}