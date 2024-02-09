/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gebuqaj <gebuqaj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 10:53:03 by gebuqaj           #+#    #+#             */
/*   Updated: 2024/02/08 11:16:54 by gebuqaj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/fdf.h"

typedef struct s_color
{
	int		r;
	int		g;
	int		b;
	int		a;
}	t_color;

uint32_t	degrade_color(t_pos a, t_pos b, int i, int steps)
{
	t_color	dif;
	t_color	new;
	float	ratio;

	ratio = (float)i / (float)steps;
	dif.r = ((a.color >> 24) & 0xFF) - ((b.color >> 24) & 0xFF);
	dif.g = ((a.color >> 16) & 0xFF) - ((b.color >> 16) & 0xFF);
	dif.b = ((a.color >> 8) & 0xFF) - ((b.color >> 8) & 0xFF);
	dif.a = (a.color & 0xFF) - (b.color & 0xFF);
	new.r = ((a.color >> 24) & 0xFF) - (dif.r * ratio);
	new.g = ((a.color >> 16) & 0xFF) - (dif.g * ratio);
	new.b = ((a.color >> 8) & 0xFF) - (dif.b * ratio);
	new.a = (a.color & 0xFF) - dif.a * ratio;
	return ((new.r << 24) | (new.g << 16) | (new.b << 8) | new.a);
}

typedef struct s_incr
{
	float	i_x;
	float	i_y;
}	t_incr;

void	draw_one_line(t_pos a_point, t_pos b_point, t_img image)
{
	int		steps;
	float	x_moving;
	float	y_moving;
	int		i;
	t_incr	incr;

	i = 0;
	x_moving = a_point.x;
	y_moving = a_point.y;
	if (abs(b_point.x - a_point.x) > abs(b_point.y - a_point.y))
		steps = abs(b_point.x - a_point.x);
	else
		steps = abs(b_point.y - a_point.y);
	incr.i_x = (float)(b_point.x - a_point.x) / (float)steps;
	incr.i_y = (float)(b_point.y - a_point.y) / (float)steps;
	while (i <= steps)
	{
		put_my_pixel(&image, (int)x_moving, (int)y_moving, degrade_color(a_point, b_point, i, steps));
		x_moving += incr.i_x;
		y_moving += incr.i_y;
		i++;
	}
}

void	draw_the_map(t_pos **list, t_img image)
{
	t_pos	*scan;

	scan = *list;
	while (scan->next != NULL)
	{
		if (scan->right != NULL)
			draw_one_line(*scan, *scan->right, image);
		if (scan->down != NULL)
			draw_one_line(*scan, *scan->down, image);
		scan = scan->next;
	}
}
