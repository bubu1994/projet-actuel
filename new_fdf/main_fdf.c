/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_fdf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gebuqaj <gebuqaj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:24:20 by gebuqaj           #+#    #+#             */
/*   Updated: 2024/02/20 14:55:50 by gebuqaj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_data(t_data mlx)
{
	printf("x_ext: %d, y_ext: %d,zoom: %f, xinit: %d, yinit: %d, alt_scale: %f\n",
	mlx.axes.x_extrem, mlx.axes.y_extrem, mlx.zoom, mlx.x_pos, mlx.y_pos, mlx.alt_scale);
}

void	change_alt(int key, t_data *mlx)
{
	if (key == ESC_K)
	{
		free_3d(mlx->points);
		exit(0);
	}
	if (key == U)
		mlx->alt_scale += mlx->delta_alt;
	if (key == J)
		mlx->alt_scale -= mlx->delta_alt;
}

void	change_color(int key, t_data *mlx)
{
	if (key == V)
	{
		mlx->color_default = 0x257C00;
		mlx->second_color = 0x78FF3D;
	}
	if (key == B)
	{
		mlx->color_default = 0xCC0000;
		mlx->second_color = 0xFF9999;
	}
	if (key == N)
	{
		mlx->color_default = 0x0000ff;
		mlx->second_color = 0x17FFFF;
	}
	if (key == M)
	{
		mlx->color_default = 0xFFFFFF;
		mlx->second_color = 0xFFFFFF;
	}
}

void	move_and_rotate(int key, t_data *mlx)
{
	if (key == LEFT_A)
		mlx->x_pos -= MOVE_A;
	if (key == UP_A)
		mlx->y_pos -= MOVE_A;
	if (key == RIGHT_A)
		mlx->x_pos += MOVE_A;
	if (key == DOWN_A)
		mlx->y_pos += MOVE_A;
	if (key == W)
		mlx->alpha += D_ANG;
	if (key == Q)
		mlx->alpha -= D_ANG;
	if (key == S)
		mlx->beta += D_ANG;
	if (key == A)
		mlx->beta -= D_ANG;
}

int	display_keypress(int key, t_data *mlx)
{
	printf("%d\n", key);
	draw_empty(*mlx);
	move_and_rotate(key, mlx);
	change_alt(key, mlx);
	change_color(key, mlx);
	draw_the_map(*mlx);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img.img_ptr, 0, 0);
	return (0);
}

int	close_x(t_data *mlx)
{
	free_3d(mlx->points);
	exit (0);
}

int	hook_mouse(int key, int x, int y, t_data *mlx)
{
	(void)x;
	(void)y;
	draw_empty(*mlx);
	if (key == 4)
		mlx->zoom += mlx->delta_zoom;
	if (key == 5)
		mlx->zoom -= mlx->delta_zoom;
	draw_the_map(*mlx);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img.img_ptr, 0, 0);
	return (0);
}

void	mlx_initialise(t_data *mlx)
{
	mlx->win = mlx_new_window(mlx->ptr, WIDTH, HEIGHT, "FDF");
	mlx->img.img_ptr = mlx_new_image(mlx->ptr, WIDTH, HEIGHT);
	mlx->img.img_pixels_ptr = mlx_get_data_addr(mlx->img.img_ptr,
		&mlx->img.bits_per_pixel, &mlx->img.line_len, &mlx->img.endian);
}

int	main(int argc, char **argv)
{
	t_data	mlx;

	if (argc != 2)
		return (0);
	mlx.ptr = mlx_init();
	mlx_initialise(&mlx);
	mlx.axes = get_width_height(argv[1]);
	mlx.points = array_of_points(argv[1], mlx.axes);
	init_env(&mlx);
	print_data(mlx);
	draw_the_map(mlx);
	mlx_put_image_to_window(mlx.ptr, mlx.win, mlx.img.img_ptr, 0, 0);
	mlx_hook(mlx.win, 2, 0, display_keypress, &mlx);
	mlx_hook(mlx.win, 17, 0, close_x, &mlx);
	mlx_mouse_hook(mlx.win, hook_mouse, &mlx);
	mlx_loop(mlx.ptr);
}
/*
les tableaux sont généralement plus adaptés lorsque la taille des données est
fixe et que les opérations d'accès aux éléments sont fréquentes, tandis que les
listes chaînées sont préférables lorsque la taille des données est variable et
que les opérations d'insertion et de suppression sont fréquentes.
*/