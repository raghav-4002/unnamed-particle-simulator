#ifndef BASIC_H     /* header guard */
#define BASIC_H


/*
 * This header consists of functions that setup the basics required to run the program.
 
 * Firstly it enables raw mode (or non-canonical mode), which gives more fine grained control
   over the terminal settings.

 * It also detects the size of terminal window using the ioctl (input-output control) syscall.
   Window size is required to place the particles and detect collision with the walls.

 */


#include <termios.h>


typedef struct {
    struct termios orig_termios;
    int screen_length;
    int screen_width;
} Attributes;

extern Attributes term_attributes;


void initialize(void);


#endif