/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_fdf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gentian <gentian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:24:20 by gebuqaj           #+#    #+#             */
/*   Updated: 2024/02/16 01:07:14 by gentian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_data(t_data mlx)
{
	printf("x_ext: %d, y_ext: %d,zoom: %d, xinit: %d, yinit: %d, alt_scale: %f\n",
	mlx.axes.x_extrem, mlx.axes.y_extrem, mlx.zoom, mlx.x_pos, mlx.y_pos, mlx.alt_scale);
}

int	display_keypress(int key, t_data *mlx)
{
	(void)mlx;
	printf("%d\n", key);
	if (key == ESC_K || key == ESC_LINUX)
		exit(0);
	return (0);
}

int	close_x()
{
	exit (0);
}

void	mlx_initialise(t_data *mlx)
{
	mlx->win = mlx_new_window(mlx->ptr, WIDTH, HEIGHT, "Alambres/Cables/Hilos");
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
	free_3d(mlx.points);
	mlx_put_image_to_window(mlx.ptr, mlx.win, mlx.img.img_ptr, 0, 0);
	mlx_key_hook(mlx.win, display_keypress, &mlx);
	mlx_hook(mlx.win, 17, 0, close_x, NULL);
	mlx_loop(mlx.ptr);
}
/*
les tableaux sont généralement plus adaptés lorsque la taille des données est
fixe et que les opérations d'accès aux éléments sont fréquentes, tandis que les
listes chaînées sont préférables lorsque la taille des données est variable et
que les opérations d'insertion et de suppression sont fréquentes.
*/