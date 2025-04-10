#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "basic.h"
#include "physics.h"


void draw(Point *point);
void move(Point particles[], unsigned size);
void set_values(Point particles[], unsigned size);


int
main(int argc, char *argv[])
{
    if(argc == 1) {
        printf("Usage: %s <number-of-particles>\n", argv[0]);
        exit(1);
    }

    unsigned particle_count = atol(argv[1]);
    Point particles[particle_count];

    srand(time(NULL));  /* seed the random number generator */
    initialize();

    set_values(particles, particle_count);
    move(particles, particle_count);    

    return 0;
}


void
set_values(Point particles[], unsigned particle_count)
{
    for(unsigned i = 0; i < particle_count; i++) {
        particles[i].position.x    = (rand() % term_attributes.screen_width) + 1;
        particles[i].position.y    = (rand() % term_attributes.screen_length) + 1;

        particles[i].velocity.x    = (rand() % 5) - 2;
        particles[i].velocity.y    = (rand() % 5) - 2;

        particles[i].accelaration.y = 0.00;
        particles[i].accelaration.x = 0.00;
    }
}


void
draw(Point *point)
{
    char buf[32];
    int  len;

    /* set cursor to new position */
    len = snprintf(buf, sizeof(buf), "\x1b[%d;%dH", 
            (int)point->position.y, (int)point->position.x);
    write(STDOUT_FILENO, buf, len);

    /* draw the particle at the new cursor position */
    write(STDOUT_FILENO, "0", 1);

    /* check for rebound from screen boundaries */
    rebound_from_edges(point);
}


void 
move(Point particles[], unsigned particle_count)
{
    const float req_frame_time = 1.0f / 40.0f;  /* target time for a single frame */
    struct timespec start, end;
    float elapsed_time, sleep_time;

    while(1) {
        clock_gettime(CLOCK_MONOTONIC, &start);
        write(STDOUT_FILENO, "\x1b[2J", 4);     /* clear the screen */

        /* redraw the particles */
        for(unsigned i = 0; i < particle_count; i++) {
            update_parameters(&particles[i]);
            draw(&particles[i]);
        }

        clock_gettime(CLOCK_MONOTONIC, &end);
        elapsed_time = (end.tv_nsec - start.tv_nsec) / (1.0e9);     /* get the actual time required to draw a frame */
        sleep_time   = req_frame_time - elapsed_time;               /* difference b/w target and actual frame time */

        /* wait for some time if differnce is greater than zero */
        if(sleep_time > 0) {
            struct timespec ts = {0, sleep_time * (1.0e9)};
            nanosleep(&ts, NULL);
        }
    }
}