SRCS := main.c projection.c shapes.c transforms.c parse.c color.c
LD := -L libft
INC := -I libft -I libft/gnl -I .
FLAGS := -g3 $(LD) $(INC) -Werror -Wextra -Wall
NAME := fdf
OBJS := $(SRCS:.c=.o)

vpath %.c srcs

all: $(NAME)

$(NAME): $(OBJS)
	@make -C libft
	gcc $(FLAGS) -lft -lmlx -framework OpenGL -framework AppKit $(OBJS) -o $(NAME)

%.o: %.c
	gcc $(INC) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean
	make all

test: re
	./$(NAME) "maps/42.fdf"

debug: re
	lldb $(NAME) "maps/42.fdf"

