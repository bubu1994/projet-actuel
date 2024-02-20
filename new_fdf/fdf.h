/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gebuqaj <gebuqaj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:28:51 by gebuqaj           #+#    #+#             */
/*   Updated: 2024/02/20 14:55:44 by gebuqaj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include "./libft/libft.h"
#include "./minilibx/mlx.h"

#include <math.h>

#define WIDTH 1800.0
#define HEIGHT 1200.0
#define GAP_W (WIDTH / 3)
#define GAP_H (HEIGHT / 3)
#define GAP_ALT (HEIGHT / 4)
#define COLOR_DEFAULT 0xFFFFFF
#define MOVE_A 20
#define D_ZOOM 1.0
#define D_ANG 0.05

#define	ESC_K 53
#define LEFT_A 123
#define UP_A 126
#define RIGHT_A 124
#define DOWN_A 125
#define W 12
#define Q 13
#define S 0
#define A 1
#define U 32
#define J 38
#define V 9
#define B 11
#define N 45
#define M 46

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
	int	temp_x;
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
	float	alpha;
	float	beta;
	float	zoom;
	float	delta_zoom;
	float	alt_scale;
	float	delta_alt;
	int		x_pos;
	int		y_pos;
	int		color_default;
	int		second_color;
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
void	draw_empty(t_data mlx);

unsigned int	pull_color(char	*s, t_data mlx);
uint32_t	degrade_color(int a, int b, int i, int steps);

int	y_tr(int y, int x, t_data mlx);
int	x_tr(int x, int y, t_data mlx);
void	init_env(t_data *mlx);
char	**ft_super_split(char *str, char *charset);



#endif