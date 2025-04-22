/*
 * Consists of functions and datatypes that are relevant for mimicking physical behaviour
   including velocity updation, position updation, rebounding from edges, collision among particles
 */


#include <stdio.h>
#include <stdlib.h>

#include "physics.h"
#include "draw.h"
#include "setup.h"


struct collision_queue{
    Point particle1;
    Point particle2;
    struct collision_queue *next;
};

struct collision_queue *front = NULL;
struct collision_queue *rear = NULL;


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
handle_collision(struct collision_queue *front)
{
    /* need to work on collision yet */
}



void
enqueue(Point particle1, Point particle2)
{
    struct collision_queue *new = malloc(sizeof(*new));
    new->next = NULL;

    if(front == NULL && rear == NULL) {
        front = new;
        rear = new;
    } else {
        rear->next = new;
        rear = rear->next;
    }

    rear->particle1 = particle1;
    rear->particle2 = particle2;
}


void
dequeue(void)
{
    handle_collision(front);

    struct collision_queue *ptr = front;
    front = front->next;
    if(front == NULL) {
        rear = NULL;
    }

    free(ptr);
}


void
handle_and_draw_particles(Point particle[], unsigned particle_count)
{
    while(front != NULL) {
        dequeue();
    }

    unsigned i, j;

    for(i = 0; i < particle_count; i++) {
        draw_particle(&particle[i]);
        rebound_from_edges(&particle[i]);
        update_position(&particle[i]);
    }       

    /* loops to check for collision */
    for(i = 0; i < particle_count - 1; i++) {
        for(j = i + 1; j < particle_count; j++) {

            /* if particles are at the same point => collision */
            if(particle[i].position.x == particle[j].position.x && 
               particle[i].position.y == particle[j].position.y) {
                enqueue(particle[i], particle[j]);
            }

            particle[j].prev_velocity.x = particle[j].current_velocity.x;
            particle[j].prev_velocity.y = particle[j].current_velocity.y;
        }

        particle[i].prev_velocity.x = particle[i].current_velocity.x;
        particle[i].prev_velocity.y = particle[i].current_velocity.y;
    }
}