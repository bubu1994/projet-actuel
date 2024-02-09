/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gebuqaj <gebuqaj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 14:28:57 by gebuqaj           #+#    #+#             */
/*   Updated: 2024/02/09 16:28:30 by gebuqaj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

typedef struct s_color
{
	int		r;
	int		g;
	int		b;
	int		a;
}	t_color;


void	put_my_pixel(t_img *img, int x, int y, int color)
{
	int	decalage;

	decalage = (y * img->line_len) + (x * (img->bits_per_pixel / 8));
	*((unsigned int *)(img->img_pixels_ptr + decalage)) = color;
}

void	draw_one_line(t_point a, t_point b, t_img image)
{
	int		steps;
	float	x_moving;
	float	y_moving;
	int		i;

	i = 0;
	x_moving = a.x;
	y_moving = a.y;
	if (abs(b.x - a.x) > abs(b.y - a.y))
		steps = abs(b.x - a.x);
	else
		steps = abs(b.y - a.y);
	a.i_x = (float)(b.x - a.x) / (float)steps;
	a.i_y = (float)(b.y - a.y) / (float)steps;
	while (i <= steps)
	{
		put_my_pixel(&image, (int)x_moving, (int)y_moving, COLOR_DEFAULT);
		x_moving += a.i_x;
		y_moving += a.i_y;
		i++;
	}
}

void	draw_the_map(t_data mlx)
{
	t_point	a;
	t_point b;
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (y < mlx.axes.y_extrem)
	{
		x = 0;
		while (x < mlx.axes.x_extrem)
		{
			a.x = x * SCALE;
			a.y = y * SCALE;
			b.x = (x + 1) * SCALE;
			b.y = y * SCALE;
			if (x < mlx.axes.x_extrem - 1)
				draw_one_line(a, b, mlx.img);
			b.x = x * SCALE;
			b.y = (y + 1) * SCALE;
			if (y < mlx.axes.y_extrem - 1)
				draw_one_line(a, b, mlx.img);
			x++;
		}
		y++;
	}
}