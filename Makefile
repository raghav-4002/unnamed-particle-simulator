FLAGS = -Wpedantic -Wextra

main: main.c
	$(CC) main.c setup.c physics.c $(FLAGS)