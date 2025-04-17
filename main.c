#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "setup.h"
#include "physics.h"


Point *particle;


void draw_frame(Point particles[], unsigned particle_count);
void set_parameters(Point particles[], unsigned size);


int
main(int argc, char *argv[])
{
    if(argc != 2) {
        printf("Usage: %s <number-of-particles>\n", argv[0]);
        exit(1);
    }

    unsigned particle_count = atol(argv[1]);
    particle = malloc(sizeof(*particle) * particle_count);

    initialize();

    set_parameters(particle, particle_count);
    draw_frame(particle, particle_count);    

    return 0;
}


void 
draw_frame(Point particles[], unsigned particle_count)
{
    const float req_frame_time = 1.0f / 60.0f;  /* target time for a single frame */
    struct timespec start, end;
    float elapsed_time, sleep_time;

    while(1) {
        clock_gettime(CLOCK_MONOTONIC, &start);
        write(STDOUT_FILENO, "\x1b[2J", 4);     /* clear the screen */

        handle_and_draw_particles(particles, particle_count);

        clock_gettime(CLOCK_MONOTONIC, &end);
        elapsed_time = (end.tv_nsec - start.tv_nsec) / (1.0e9);     /* get the actual time required to draw a frame */
        sleep_time   = req_frame_time - elapsed_time;               /* difference b/w target and actual frame time */

        /* wait for some time if difference is greater than zero */
        if(sleep_time > 0) {
            struct timespec ts = {0, sleep_time * (1.0e9)};
            nanosleep(&ts, NULL);
        }
    }
}


void
set_parameters(Point particles[], unsigned particle_count)
{
    for(unsigned i = 0; i < particle_count; i++) {
        particles[i].position.x    = (rand() % term_attributes.screen_width) + 1;
        particles[i].position.y    = (rand() % term_attributes.screen_length) + 1;

        particles[i].velocity.x    = (rand() % 5) - 2;
        particles[i].velocity.y    = (rand() % 5) - 2;
    }
}