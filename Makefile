CC =		gcc

RM =		rm -f

CFLAGS =	-Wall -Werror -Wextra -g3

LDFLAGS =	-lpthread  -lSDLmain -lSDL -lSDL_image

SRC =		main.c \
		sdl.c \
		table.c \
		rods.c \
		philosopher_job.c \

OBJ =		$(SRC:.c=.o)

NAME =		philo

all:		$(NAME)

$(NAME):	$(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean:		clean
	$(RM) $(NAME)

re: fclean all

.PHONY: re all clean fclean
