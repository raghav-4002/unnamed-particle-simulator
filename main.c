#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "basic.h"
#include "physics.h"


/*
 * for smoother experience only use values of velocity from 0 to 3
 * And the values of accelaration from 0 to 1 (floats are ok)
 */
#define X_VELOCITY     0
#define Y_VELOCITY     0

#define X_ACCELARATION 0
#define Y_ACCELARATION 0

#define MASS           2.5

#define X_FORCE        0
#define Y_FORCE        0

#define OBJECT        "O"


void draw(Point *point);
void move(Point *point);


int
main(void)
{
    initialize();

    Point point = {MASS,
    {0, 0},
    {X_VELOCITY, Y_VELOCITY},
    {X_ACCELARATION, Y_ACCELARATION}, 
    OBJECT};

    Vector2 force = {0.1, 0};

    apply_force(&point, force);

    return 0;
}


void
draw(Point *point)
{
    write(STDOUT_FILENO, "\x1b[2J", 4);
    char buf[32];
    int  len;

    len = snprintf(buf, sizeof(buf), "\x1b[%d;%dH", (int)point->position.y, (int)point->position.x);

    write(STDOUT_FILENO, buf, len);

    write(STDOUT_FILENO, point->symbol, sizeof(point->symbol));
}


void 
move(Point *point)
{
    struct timespec  ts = {0, 63000000};
    struct timespec *n = NULL;

    while(1) {
        point->velocity.x += point->accelaration.x;
        point->velocity.y += point->accelaration.y;
        point->position.x += point->velocity.x;
        point->position.y += point->velocity.y;

        draw(point);

        nanosleep(&ts, n);
    }
}