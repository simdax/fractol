all:
	gcc -g3 -lmlx -framework OpenGL -framework AppKit main.c

test: all
	./a.out

debug: all
	lldb a.out
