FLAGS = -Wpedantic -Wextra

main: main.c
	$(CC) main.c basic.c physics.c $(FLAGS)