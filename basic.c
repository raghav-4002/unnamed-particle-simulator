#include "basic.h"
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <stdio.h>


Attributes term_attributes;


void
kill(const char *message)
{
    perror(message);

    exit(1);
}

void
disable_raw_mode(void)
{
    /* during exit, restore the original terminal attributes */
    if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &term_attributes.orig_termios) == -1)
        kill("tcsetattr");

    /* unhide cursor */
    write(STDOUT_FILENO, "\x1b[?25h", 6);
}


void
enable_raw_mode(void)
{
    /* get terminal attributes */
    if(tcgetattr(STDIN_FILENO, &term_attributes.orig_termios) == -1)
        kill("tcgetattr");
    
    atexit(disable_raw_mode);

    struct termios raw;
    
    /* settings to enable raw mode */
    raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN | CS8);
	raw.c_iflag &= ~(IXON | ICRNL | BRKINT | INPCK | ISTRIP);
	raw.c_oflag &= ~(OPOST);
	raw.c_cflag |= (CS8);

    /* set the updated terminal attributes */
    if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
        kill("tcsetattr");
}


void
get_window_size(void)
{
    struct winsize ws;

    /* using ioctl to get window size in the struct pointed by ws */
    if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1)
        kill("ioctl");

    term_attributes.screen_length = ws.ws_row;
    term_attributes.screen_width  = ws.ws_col;
}


void
initialize(void)
{
    enable_raw_mode();
    get_window_size();

    /* clear the screen */
    write(STDOUT_FILENO, "\x1b[2J", 4);

    /* hide cursor */
    write(STDOUT_FILENO, "\x1b[?25l", 6);
}