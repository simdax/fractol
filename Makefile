LFT_SRCS := gnl/get_next_line.c ft_bzero.c ft_memcpy.c ft_strchr.c ft_strdup.c ft_strlen.c ft_strsplit.c ft_atoi.c ft_issep.c ft_isdigit.c ft_lstadd.c ft_lstnew.c
SRCS := main.c shapes.c transforms.c parse.c $(addprefix libft/, $(LFT_SRCS))
LD := -L libft
INC := -I libft -I libft/gnl
FLAGS := -g3 $(LD) $(INC)

all:
	gcc $(FLAGS) -lft -lmlx -framework OpenGL -framework AppKit $(SRCS)

test: all
	./a.out

debug: all
	lldb a.out

