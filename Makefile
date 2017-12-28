SRCS = main.c shapes.c transforms.c

all:
	gcc -g3 -lmlx -framework OpenGL -framework AppKit $(SRCS)

test: all
	./a.out

debug: all
	lldb a.out

