#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>


struct {
    struct termios orig_termios;
    int screen_length, screen_width;
} attributes;

typedef struct {
    int x;
    int y;
} Vector2;

typedef struct {
    Vector2 position;
    Vector2 velocity;

    char object[8];
} Point;


void init(void);
void draw(Point *point);
void move(Point *point);
void get_window_size(void);
void enable_raw_mode(void);
void disable_raw_mode(void);
void kill(const char *message);


int
main(void)
{
    init();

    Point point = {{attributes.screen_width / 2, 20}, {1, 0}, "/"};

    move(&point);

    return 0;
}


void
init(void)
{
    enable_raw_mode();
    get_window_size();

    /* hide cursor */
    write(STDOUT_FILENO, "\x1b[?25l", 6);
}


void
draw(Point *point)
{
    write(STDOUT_FILENO, "\x1b[2J", 4);
    char buf[32];
    int len;

    len = snprintf(buf, sizeof(buf), "\x1b[%d;%dH", point->position.y, point->position.x);

    write(STDOUT_FILENO, buf, len);

    write(STDOUT_FILENO, point->object, sizeof(point->object));
}


void 
move(Point *point)
{
    while(1) {
        point->position.x += point->velocity.x;
        point->position.y += point->velocity.y;

        draw(point);

        sleep(1);
    }
}


void
get_window_size(void)
{
    struct winsize ws;

    if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1) kill("ioctl");

    attributes.screen_length = ws.ws_row;
    attributes.screen_width = ws.ws_col;
}


void
enable_raw_mode(void)
{
    if(tcgetattr(STDIN_FILENO, &attributes.orig_termios) == -1) kill("tcgetattr");
    atexit(disable_raw_mode);

    struct termios raw = attributes.orig_termios;

    raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN | CS8);
	raw.c_iflag &= ~(IXON | ICRNL | BRKINT | INPCK | ISTRIP);
	raw.c_oflag &= ~(OPOST);
	raw.c_cflag |= (CS8);

    if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) kill("tcsetattr");
}


void
disable_raw_mode(void)
{
    if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &attributes.orig_termios) == -1) kill("tcsetattr");

    /* unhide cursor */
    write(STDOUT_FILENO, "\x1b[?25h", 6);
}


void
kill(const char *message)
{
    perror(message);

    exit(1);
}