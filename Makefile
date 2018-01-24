NAME := fdf
SRCS := main.c projection.c shapes.c transforms.c parse.c color.c
LD := -L lft
INC := -I lft -I lft/gnl -I .
FLAGS := -g3 $(LD) $(INC) -Werror -Wextra -Wall
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
	./$(NAME) "maps/42.fdf"

simple: re
	./$(NAME) "simple"

debug: re
	lldb $(NAME) "maps/42.fdf"

