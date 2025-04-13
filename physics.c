#include "physics.h"
#include "draw.h"
#include "setup.h"


void
update_velocity(Point *point1, Point *point2)
{
    // check which one hits which one
    // generalize for both 2-d and 1-d motion
}


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
detect_collision(Point particles[], unsigned particle_count, unsigned i)
{
    Vector2 i_next_position = {particles[i].position.x + particles[i].velocity.x, 
                                particles[i].position.y + particles[i].velocity.y};

    for(int j = i + 1; j < particle_count; j++) {
        Vector2 j_next_position = {particles[j].position.x + particles[j].velocity.x,
                                    particles[j].position.y + particles[j].velocity.y};

        if(i_next_position.x == j_next_position.x && i_next_position.y == j_next_position.y) {
            // both particles will collide in the next frame
        }
    }
}


void
update_parameters(Point particles[], unsigned particle_count)
{
    for(unsigned i = 0; i < particle_count; i++) {
        draw(&particles[i]);
        rebound_from_edges(&particles[i]);
        update_position(&particles[i]);

        detect_collision(particles, particle_count, i);
    }       
}