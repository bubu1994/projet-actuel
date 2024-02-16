/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gentian <gentian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 10:53:29 by gentian           #+#    #+#             */
/*   Updated: 2024/02/16 01:07:07 by gentian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	scale_alt(char ***tab)
{
	int	y;
	int	x;
	int	z;
	int	max_z;
	float	scale;

	y = 0;
	max_z = 0;
	scale = 1;
	while (tab[y])
	{
		x = 0;
		while (tab[y][x])
		{
			z = abs(ft_atoi(tab[y][x]));
			if (z > max_z)
				max_z = z;
			x++;
		}
		y++;
	}
	scale = HEIGHT / 5.0 / max_z;
	return (scale);
}

void    init_zoom(t_data *mlx)
{
	int	x_zoom;
	int	y_zoom;

	x_zoom = (WIDTH - 2 * GAP_W) / mlx->axes.x_extrem;
	y_zoom = (HEIGHT - 2 * GAP_H) / mlx->axes.y_extrem;
    if (x_zoom > y_zoom)
		mlx->zoom = y_zoom;
	else
		mlx->zoom = x_zoom;
}

int	get_xinit(t_data mlx)
{
	int	dx;
	int	res;

	dx = x_tr(mlx.axes.x_extrem, 0, mlx) + x_tr(0, mlx.axes.y_extrem, mlx);
	res = (WIDTH - dx) / 2;
	return (res);
}

int	get_yinit(t_data mlx)
{
	int	dy;
	int	res;

	dy = y_tr(mlx.axes.y_extrem - 1, mlx.axes.x_extrem - 1, mlx);
	res = (HEIGHT - dy) / 2;
	return (res);
}

void	init_env(t_data *mlx)
{
	init_zoom(mlx);
	mlx->alt_scale = scale_alt(mlx->points);
	mlx->x_pos = get_xinit(*mlx);
	mlx->y_pos = get_yinit(*mlx);
}