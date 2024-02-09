/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gebuqaj <gebuqaj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 10:20:26 by gebuqaj           #+#    #+#             */
/*   Updated: 2024/02/08 12:32:52 by gebuqaj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/fdf.h"

void	print_lst(t_pos **lst)
{
	t_pos	*scan;

	scan = *lst;
	while (scan != NULL)
	{
		printf("x: %d, y: %d, z: %d, color: %x\n", scan->x, scan->y, scan->z, scan->color);
		scan = scan->next;
	}
}

void	matrix_the_points(t_pos *point)
{
	int	x_temp;

	while (point)
	{
		x_temp = point->x;
		point->x = point->x - point->y;
		point->y = ((x_temp + point->y) / 2) - point->z * ALT_SCALE;
		point = point->next;
	}
}

void	scale_it(t_pos **list)
{
	t_pos	*scan;

	scan = *list;
	while (scan)
	{
		scan->x = scan->x * SCALE_IMG;
		scan->y = scan->y * SCALE_IMG;
		scan = scan->next;
	}
}

void	simple_isometric(t_pos **list)
{
	t_pos	*scan;
	t_pos	*last;
	float	gap;
	int		x_temp;

	scan = *list;
	last = last_elem(list);
	if (((float)(IMG_WIDTH - 1) / (float)last->x) > ((float)(IMG_HEIGHT - 1) / (float)last->y))
		gap = ((IMG_HEIGHT - 1) / (float)last->y) * SCALE_IMG;
	else
		gap = ((float)(IMG_WIDTH - 1) / (float)last->x) * SCALE_IMG;
	while (scan)
	{
		x_temp = scan->x * gap;
		scan->x = (scan->x * gap) - (scan->y * gap);
		scan->y = ((scan->y * gap) + x_temp) / 2 - (scan->z * ALT_SCALE);
		scan = scan->next;
	}
}

int	close_esc(int key, t_data *mlx)
{
	if (key == ESCAPE_K)
	{
		mlx_destroy_window(mlx->ptr, mlx->win);
		exit(0);
	}
	return (0);
}

int close_x(int key, t_data *mlx)
{
	mlx_destroy_window(mlx->ptr, mlx->win);
	exit(0);
}

int key_press(int key, t_data *mlx)
{
	printf("%d\n", key);
	return (0);
}

void resize(int width, int height, void *ptr, void *win)
{
	mlx_clear_window(ptr, win);
	mlx_destroy_window(ptr, win);

	win = mlx_new_window(ptr, width, height, "new");
}

int	main(int argc, char **argv)
{
	t_data	mlx;
	int		fd;
	t_pos	*ma_liste;
	
	mlx.ptr = mlx_init();
	mlx.win = mlx_new_window(mlx.ptr, WIDTH, HEIGHT, "Mi ventana");
	mlx.img.img_ptr = mlx_new_image(mlx.ptr, IMG_WIDTH, IMG_HEIGHT);
	mlx.img.img_pixels_ptr = mlx_get_data_addr(mlx.img.img_ptr, &mlx.img.bits_per_pixel, &mlx.img.line_len, &mlx.img.endian);

 	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		exit (1);
	}
	ma_liste = create_list_pos(fd);
	close(fd);
 	full_spread(&ma_liste);
	scale_it(&ma_liste);
	matrix_the_points(ma_liste);
	center_points_in_image(&ma_liste);
//	print_lst(&ma_liste);

	mlx.list = ma_liste;
	draw_the_map(&(mlx.list), mlx.img);
	mlx_put_image_to_window(mlx.ptr, mlx.win, mlx.img.img_ptr, 0, 0);
	free_lst(ma_liste);
	mlx_key_hook(mlx.win, close_esc, &mlx);
	mlx_hook(mlx.win, 17, 1L<<0, close_x, &mlx);
	mlx_loop(mlx.ptr);
	return (0);
}
