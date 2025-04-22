#ifndef BASIC_H     /* header guard */
#define BASIC_H




#include <termios.h>


typedef struct {
    struct termios orig_termios;
    int screen_length;
    int screen_width;
} Attributes;

extern Attributes term_attributes;


void initialize(void);


#endif