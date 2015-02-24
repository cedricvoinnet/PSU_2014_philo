CC =		gcc

RM =		rm -f

CFLAGS =	-Wall -Werror -Wextra

LDFLAGS =	-lpthread

SRC =		main.c

OBJ =		$(SRC:.c=.o)

NAME =		philo

all:		$(NAME)

$(NAME):	$(OBJ)
	$(CC) $(OBJ) -o $(NAME)

%.o:		%.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ -c $<

clean:
	$(RM) $(OBJ)

fclean:		clean
	$(RM) $(NAME)

re: fclean all

.PHONY: re all clean fclean
