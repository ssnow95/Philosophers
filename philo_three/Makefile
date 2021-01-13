NAME = philosophers

SRCS = main.c help_function.c inits.c death.c main2.c help_function2.c

OBJS = $(SRCS:.c=.o)
HEADER = philosophers.h

all: $(NAME)

$(NAME): $(OBJS) $(HEADER)
	gcc $(OBJS) -Wall -Wextra -g -Werror 

$(OBJS): %.o:%.c $(HEADER)
		gcc -c  -Wall -Wextra -g -Werror $< -o $@

clean:
	/bin/rm -f *.o

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
