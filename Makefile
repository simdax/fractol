NAME := fractol
SRCS := main.c color.c mandelbrot.c thread.c callbacks.c callbacks2.c mandelbrot_fs.c
LD := -L lft
INC := -I srcs -I lft
FLAGS := $(LD) $(INC) -g3 -Werror -Wextra -Wall -O3 -flto -march=native
OBJS := $(SRCS:%.c=objs/%.o)

vpath %.c srcs

all: $(NAME)

$(NAME): $(OBJS)
	@make -C lft
	gcc $(FLAGS) -lft -lmlx -framework OpenGL -framework AppKit $(OBJS) -o $(NAME)

objs/%.o: %.c | objs
	gcc -g3 $(INC) -c $< -o $@

objs:
	mkdir -p objs

clean:
	@make -C lft clean
	rm -rf $(OBJS)

fclean: clean
	@make -C lft fclean
	rm -rf $(NAME)

re: fclean
	@make -C lft re
	make all

test: re
	./$(NAME) mandelbrot

debug: re
	lldb $(NAME)
