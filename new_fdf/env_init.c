/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gebuqaj <gebuqaj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 10:53:29 by gentian           #+#    #+#             */
/*   Updated: 2024/02/20 14:37:29 by gebuqaj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	scale_alt(t_data mlx)
{
	int	y;
	int	x;
	int	z;
	int	max_z;
	float	scale;

	y = 0;
	max_z = 1;
	scale = 1;
	while (mlx.points[y])
	{
		x = 0;
		while (mlx.points[y][x])
		{
			z = abs(ft_atoi(mlx.points[y][x]));
			if (z > max_z)
				max_z = z;
			x++;
		}
		y++;
	}
	scale = HEIGHT / 4.0 / max_z / mlx.zoom;
	return (scale);
}

void    init_zoom(t_data *mlx)
{
	float	x_zoom;
	float	y_zoom;

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

	dy = y_tr(mlx.axes.y_extrem, mlx.axes.x_extrem, mlx);
	res = (HEIGHT - dy) / 2;
	return (res);
}

void	init_env(t_data *mlx)
{
	mlx->alpha = M_PI * 2;
	mlx->beta = M_PI * 2;
	init_zoom(mlx);
	mlx->alt_scale = scale_alt(*mlx);
	mlx->x_pos = get_xinit(*mlx);
	mlx->y_pos = get_yinit(*mlx);
	mlx->delta_zoom = mlx->zoom / 20;
	mlx->delta_alt = mlx->alt_scale / 20;
	mlx->color_default = 0xffffff;
	mlx->second_color = 0xffffff;
}