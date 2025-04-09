#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "basic.h"
#include "physics.h"


#define SIZE 100

Point particles[SIZE];


void draw(Point *point);
void move(void);
void set_values(void);


int
main(void)
{
    srand(time(NULL));
    initialize();

    set_values();

    move();    

    return 0;
}


void
set_values(void)
{
    for(int i = 0; i < SIZE; i++) {
        particles[i].position.x = (rand() % term_attributes.screen_width) + 1;
        particles[i].position.y = (rand() % term_attributes.screen_length) + 1;

        particles[i].velocity.x = 0;
        particles[i].velocity.y = 0;

        particles[i].accelaration.y = (((float)rand()) / RAND_MAX);
        particles[i].accelaration.x = (((float)rand()) / RAND_MAX);
    }
}


void
draw(Point *point)
{
    char buf[32];
    int  len;

    len = snprintf(buf, sizeof(buf), "\x1b[%d;%dH", (int)point->position.y, (int)point->position.x);

    write(STDOUT_FILENO, buf, len);

    write(STDOUT_FILENO, "0", 1);

    if(point->position.x >= term_attributes.screen_width || point->position.x <= 0) {
        point->velocity.x *= -1;
        point->accelaration.x *= -0.1;
    }

    if(point->position.y >= term_attributes.screen_length || point->position.y <= 0) {
        point->velocity.y *= -1;
        point->accelaration.y *= -0.1;
    }
}


void 
move(void)
{
    const float req_frame_time = 1.0f / 60.0f;
    struct timespec start, end;
    float elapsed_time, sleep_time;

    while(1) {
        clock_gettime(CLOCK_MONOTONIC, &start);

        write(STDOUT_FILENO, "\x1b[2J", 4);
        for(int i = 0; i < SIZE; i++) {
            particles[i].velocity.x += particles[i].accelaration.x;
            particles[i].velocity.y += particles[i].accelaration.y;

            particles[i].position.x += particles[i].velocity.x;
            particles[i].position.y += particles[i].velocity.y;

            draw(&particles[i]);

            
        }
        clock_gettime(CLOCK_MONOTONIC, &end);

        elapsed_time = (end.tv_nsec - start.tv_nsec) / (1.0e9);

        sleep_time = req_frame_time - elapsed_time;

        if(sleep_time > 0) {
            struct timespec ts = {0, sleep_time * (1.0e9)};

            nanosleep(&ts, NULL);
        }
    }
}