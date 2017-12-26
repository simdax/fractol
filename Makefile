all:
	gcc -g -lmlx -framework OpenGL -framework AppKit main.c

test: all
	./a.out