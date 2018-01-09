SRCS = main.c test_sort.c

all:
	gcc -g3 ../*.o $(SRCS)

do: all
	./a.out

libft:
	cd .. && make
	gcc ../*.o *.o testLibft.c && ./a.out
