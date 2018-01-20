NAME := fdf
SRCS := main.c projection.c shapes.c transforms.c parse.c color.c print.c
LD := -L lft
INC := -I lft -I lft/gnl -I .
FLAGS := -g3 $(LD) $(INC) -Werror -Wextra -Wall
OBJS := $(SRCS:.c=.o)

vpath %.c srcs

all: $(NAME)

$(NAME): $(OBJS)
	@make -C lft
	gcc $(FLAGS) -lft -lmlx -framework OpenGL -framework AppKit $(OBJS) -o $(NAME)

%.o: %.c
	gcc -g3 $(INC) -c $< -o $@

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

