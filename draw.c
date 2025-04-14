#include <stdio.h>
#include <unistd.h>

#include "draw.h"


void
draw_particle(Point *point)
{
    char buf[32];
    int  len;

    /* set cursor to new position */
    len = snprintf(buf, sizeof(buf), "\x1b[%d;%dH", 
            (int)point->position.y, (int)point->position.x);
    write(STDOUT_FILENO, buf, len);

    /* draw the particle at the new cursor position */
    write(STDOUT_FILENO, "O", 1);
}