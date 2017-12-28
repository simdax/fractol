SRCS := main.c shapes.c transforms.c parse.c
LD := -L libft
FLAGS := -g3 $(LD)

all:
	make -C libft
	gcc $(FLAGS) -lft -lmlx -framework OpenGL -framework AppKit $(SRCS)

test: all
	./a.out

debug: all
	lldb a.out

