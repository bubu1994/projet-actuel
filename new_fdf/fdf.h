/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gentian <gentian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:28:51 by gebuqaj           #+#    #+#             */
/*   Updated: 2024/02/16 01:07:04 by gentian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include "./libft/libft.h"
#include "./minilibx/mlx.h"

#include <math.h>

#define WIDTH 1400
#define HEIGHT 1000.0
#define GAP_W (WIDTH / 5)
#define GAP_H (HEIGHT / 5)
#define GAP_ALT (HEIGHT / 4)
#define COLOR_DEFAULT 0xFFFFFF

#define	ESC_K 53

#define ESC_LINUX 65307

typedef struct s_img
{
	void	*img_ptr;
	char	*img_pixels_ptr;
	int		bits_per_pixel;
	int		endian;
	int		line_len;
}	t_img;

typedef struct s_axes
{
	int	x_extrem;
	int	y_extrem;
}	t_axes;

typedef struct s_point
{
	int		x;
	int		y;
	int		z;
	float	i_x;
	float	i_y;
}	t_point;

typedef struct s_color
{
	int		r;
	int		g;
	int		b;
	int		a;
}	t_color;

typedef struct s_data
{
	void	*ptr;
	void	*win;
	char	***points;
	int		zoom;
	float	alt_scale;
	int		x_pos;
	int		y_pos;
	t_axes	axes;
	t_img	img;
}	t_data;


void	free_tableau(char **tab);
void	free_3d(char ***array);

t_axes	get_width_height(char *file);
void	fd_open_error(int fd);

char	***array_of_points(char *file, t_axes axes);
void	put_my_pixel(t_img *img, int x, int y, int color);
void	draw_one_line(t_point a, t_point b, t_data mlx);
void	draw_the_map(t_data mlx);
unsigned int	pull_color(char	*s);
unsigned int	degrade_color(unsigned int a, unsigned int b, int i, int steps);
int	y_tr(int y, int x, t_data mlx);
int	x_tr(int x, int y, t_data mlx);
void	init_env(t_data *mlx);



#endif