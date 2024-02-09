/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gebuqaj <gebuqaj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:28:51 by gebuqaj           #+#    #+#             */
/*   Updated: 2024/02/09 16:27:06 by gebuqaj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include "./libft/libft.h"
#include "./minilibx/mlx.h"

#include <math.h>

#define WIDTH 1400
#define HEIGHT 1000

#define COLOR_DEFAULT 0xFFFFFF
#define SCALE 20

#define	ESC_K 53

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

typedef struct s_data
{
	void	*ptr;
	void	*win;
	char	***points;
	t_axes	axes;
	t_img	img;
}	t_data;

typedef struct s_point
{
	int		x;
	int		y;
	float	i_x;
	float	i_y;
}	t_point;


void	free_tableau(char **tab);
void	free_3d(char ***array);

t_axes	get_width_height(char *file);
void	fd_open_error(int fd);

char	***array_of_points(char *file, t_axes axes);
void	put_my_pixel(t_img *img, int x, int y, int color);
void	draw_one_line(t_point a, t_point b, t_img image);
void	draw_the_map(t_data mlx);


#endif