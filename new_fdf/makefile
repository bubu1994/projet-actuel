NAME = fdf

CC = gcc

FLAGS = -Wall -Werror -Wextra

MAC_FWs = -framework OpenGL -framework Appkit

SRC = main_fdf.c utils.c draw.c env_init.c pull_color.c ft_super_split.c\

OBJ = ${SRC:.c=.o}

%.o: %.c
	${CC} ${FLAGS} -c $< -o $@

${NAME}: ${OBJ}
	make -s -C libft
	make -s -C minilibx
	${CC} ${OBJ} -Llibft -lft -Lminilibx -lmlx ${MAC_FWs} -o ${NAME}

all:	${NAME}

clean:
	make clean -s -C libft
	make clean -s -C minilibx
	rm -f ${OBJ}

fclean:	clean
	rm -f ${NAME}

re: fclean all