#include <termios.h>
#include <unistd.h>
#include <stdlib.h>


struct {
    struct termios orig_termios;
} attributes;


void enable_raw_mode(void);
void disable_raw_mode(void);


int
main(void)
{
    enable_raw_mode();

    return 0;
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
}