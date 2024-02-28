NAME =		philo

CC =		cc

FLAGS =		-Wall -Werror -Wextra

SRC = 		main_philo.c utils.c

OBJ = ${SRC:.c=.o}

%.o: %.c
	${CC} ${FLAGS} -c $< -o $@

${NAME}: ${OBJ}
	${CC} ${OBJ} -o ${NAME}

all:	${NAME}

clean:
	rm -f ${OBJ}

fclean:	clean
	rm -f ${NAME}

re: fclean all