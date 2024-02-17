/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gebuqaj <gebuqaj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 14:28:57 by gebuqaj           #+#    #+#             */
/*   Updated: 2024/02/17 10:36:31 by gebuqaj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_my_pixel(t_img *img, int x, int y, int color)
{
	int	decalage;

	decalage = (y * img->line_len) + (x * (img->bits_per_pixel / 8));
	*((unsigned int *)(img->img_pixels_ptr + decalage)) = color;
}

int	x_tr(int x, int y, t_data mlx)
{
	int	x_prim;
	int	y_prim;
	
	x_prim = x * mlx.zoom;
	y_prim = y * mlx.zoom;
	x_prim = (x_prim - y_prim) * cos(mlx.alpha);
	return (x_prim);
}

int	y_tr(int y, int x, t_data mlx)
{
	int	x_prim;
	int	y_prim;
	float	z;

	z = ft_atoi(mlx.points[y][x]) * mlx.alt_scale * mlx.zoom;
	x_prim = x * mlx.zoom;
	y_prim = y * mlx.zoom;
	y_prim = ((x_prim + y_prim) / 2) * sin(mlx.beta) - z;
	return (y_prim);
}

void	draw_one_line(t_point a, t_point b, t_data mlx)
{
	int		steps;
	float	x;
	float	y;
	int		i;

	i = 0;
	x = x_tr(a.x, a.y, mlx);
	y = y_tr(a.y, a.x, mlx);
	if (abs(x_tr(b.x, b.y, mlx) - x_tr(a.x, a.y, mlx)) > abs(y_tr(b.y, b.x, mlx) - y_tr(a.y, a.x, mlx)))
		steps = abs(x_tr(b.x, b.y, mlx) - x_tr(a.x, a.y, mlx));
	else
		steps = abs(y_tr(b.y, b.x, mlx) - y_tr(a.y, a.x, mlx));
	a.i_x = (float)(x_tr(b.x, b.y, mlx) - x_tr(a.x, a.y, mlx)) / (float)steps;
	a.i_y = (float)(y_tr(b.y, b.x, mlx) - y_tr(a.y, a.x, mlx)) / (float)steps;
	while (i <= steps)
	{
		put_my_pixel(&mlx.img, (int)x + mlx.x_pos, (int)y + mlx.y_pos,
		degrade_color(pull_color(mlx.points[a.y][a.x]), pull_color(mlx.points[b.y][b.x]), i, steps));
		x += a.i_x;
		y += a.i_y;
		i++;
	}
}

void	draw_the_map(t_data mlx)
{
	t_point	a;
	t_point b;
	int		x;
	int		y;

	y = 0;
	while (y < mlx.axes.y_extrem)
	{
		x = 0;
		while (x < mlx.axes.x_extrem)
		{
			a.x = x;
			a.y = y;
			a.z = ft_atoi(mlx.points[y][x]);
			b.x = x + 1;
			b.y = y;
			b.z = ft_atoi(mlx.points[y][x]);
			if (x < mlx.axes.x_extrem - 1)
				draw_one_line(a, b, mlx);
			b.x = x;
			b.y = y + 1;
			if (y < mlx.axes.y_extrem - 1)
				draw_one_line(a, b, mlx);
			x++;
		}
		y++;
	}
}

void	draw_one_black_line(t_point a, t_point b, t_data mlx)
{
	int		steps;
	float	x;
	float	y;
	int		i;

	i = 0;
	x = x_tr(a.x, a.y, mlx);
	y = y_tr(a.y, a.x, mlx);
	if (abs(x_tr(b.x, b.y, mlx) - x_tr(a.x, a.y, mlx)) > abs(y_tr(b.y, b.x, mlx) - y_tr(a.y, a.x, mlx)))
		steps = abs(x_tr(b.x, b.y, mlx) - x_tr(a.x, a.y, mlx));
	else
		steps = abs(y_tr(b.y, b.x, mlx) - y_tr(a.y, a.x, mlx));
	a.i_x = (float)(x_tr(b.x, b.y, mlx) - x_tr(a.x, a.y, mlx)) / (float)steps;
	a.i_y = (float)(y_tr(b.y, b.x, mlx) - y_tr(a.y, a.x, mlx)) / (float)steps;
	while (i <= steps)
	{
		put_my_pixel(&mlx.img, (int)x + mlx.x_pos, (int)y + mlx.y_pos, 0x000000);
		x += a.i_x;
		y += a.i_y;
		i++;
	}
}

void	draw_empty(t_data mlx)
{
	t_point	a;
	t_point b;
	int		x;
	int		y;

	y = 0;
	while (y < mlx.axes.y_extrem)
	{
		x = 0;
		while (x < mlx.axes.x_extrem)
		{
			a.x = x;
			a.y = y;
			a.z = ft_atoi(mlx.points[y][x]);
			b.x = x + 1;
			b.y = y;
			b.z = ft_atoi(mlx.points[y][x]);
			if (x < mlx.axes.x_extrem - 1)
				draw_one_black_line(a, b, mlx);
			b.x = x;
			b.y = y + 1;
			if (y < mlx.axes.y_extrem - 1)
				draw_one_black_line(a, b, mlx);
			x++;
		}
		y++;
	}
}