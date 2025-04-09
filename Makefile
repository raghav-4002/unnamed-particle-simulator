FLAGS = -Wpedantic -Wextra

main: main.c
	$(CC) main.c basic.c $(FLAGS)