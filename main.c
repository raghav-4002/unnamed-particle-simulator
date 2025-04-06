#include <termios.h>
#include <unistd.h>
#include <stdlib.h>


struct {
    struct termios orig_termios;
} attributes;


void init(void);
void enable_raw_mode(void);
void disable_raw_mode(void);


int
main(void)
{
    init();

    return 0;
}


void
init(void)
{
    enable_raw_mode();

    /* clear screen */
    write(STDOUT_FILENO, "\x1b[2J", 4);
    /* hide cursor */
    write(STDOUT_FILENO, "\x1b[?25l", 6);
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