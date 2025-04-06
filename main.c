#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <time.h>


struct {
    struct termios orig_termios;
    int screen_length, screen_width;
    int cx, cy;
} attributes;


void init(void);
void draw(void);
void move(void);
void get_window_size(void);
void enable_raw_mode(void);
void disable_raw_mode(void);


int
main(void)
{
    init();
    move();

    return 0;
}


void
init(void)
{
    enable_raw_mode();
    get_window_size();

    /* initialize cursor position */
    attributes.cx = attributes.screen_width / 2;
    attributes.cy = 0;

    /* hide cursor */
    write(STDOUT_FILENO, "\x1b[?25l", 6);
}


void
draw(void)
{
    write(STDOUT_FILENO, "\x1b[2J", 4);
    char buf[32];
    int len;

    len = snprintf(buf, sizeof(buf), "\x1b[%d;%dH", attributes.cy, attributes.cx);

    write(STDOUT_FILENO, buf, len);

    write(STDOUT_FILENO, "*", 1);
}


void move(void)
{
    struct timespec ts = {0, 70000000};
    struct timespec *rem = NULL;

    while(attributes.cy != attributes.screen_length) {
        attributes.cy++;
        draw();
        nanosleep(&ts, rem);
    }
}


void
get_window_size(void)
{
    struct winsize ws;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);

    attributes.screen_length = ws.ws_row;
    attributes.screen_width = ws.ws_col;
}


void
enable_raw_mode(void)
{
    tcgetattr(STDIN_FILENO, &attributes.orig_termios);
    atexit(disable_raw_mode);

    struct termios raw = attributes.orig_termios;

    raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN | CS8);
	raw.c_iflag &= ~(IXON | ICRNL | BRKINT | INPCK | ISTRIP);
	raw.c_oflag &= ~(OPOST);
	raw.c_cflag |= (CS8);

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}


void
disable_raw_mode(void)
{
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &attributes.orig_termios);

    /* unhide cursor */
    write(STDOUT_FILENO, "\x1b[?25h", 6);
}