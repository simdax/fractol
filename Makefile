NAME := fractol
SRCS := main.c color.c mandelbrot.c thread.c callbacks.c
LD := -L lft
INC := -I lft -I lft/gnl -I srcs
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
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean
	make all

test: re
	./$(NAME) io ia

debug: re
	lldb $(NAME)
