NAME = fdf

CC = gcc

FLAGS = -Wall -Werror -Wextra

MAC_FWs = -framework OpenGL -framework Appkit

SRC = main_fdf.c utils.c draw.c pull_color.c env_init.c\

OBJ = ${SRC:.c=.o}

%.o: %.c
	$(CC) $(FLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@

${NAME}: ${OBJ}
	make -s -C libft
	make -s -C mlx_linux
	$(CC) $(OBJ) -Llibft -lft -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

all:	${NAME}

clean:
	make clean -s -C libft
	make clean -s -C mlx_linux
	rm -f ${OBJ}

fclean:	clean
	rm -f ${NAME}

re: fclean all