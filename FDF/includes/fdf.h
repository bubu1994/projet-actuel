/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gebuqaj <gebuqaj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 15:12:02 by gebuqaj           #+#    #+#             */
/*   Updated: 2024/02/07 19:06:13 by gebuqaj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include "get_next_line.h"
#include "libft.h"
#include "mlx.h"

#include <stdio.h>
#include <fcntl.h>
#include <math.h>

#define WIDTH 1600
#define HEIGHT 1100
#define IMG_WIDTH (WIDTH)
#define IMG_HEIGHT (HEIGHT)
#define	SCALE_IMG 0.5
#define ALT_SCALE 1
#define Y_ANGLE 0.7854
#define Z_ANGLE 0.5236
#define GAP 300
#define COLOR_DEFAULT 0xFFFFFF

#define ESCAPE_K 53

typedef struct s_img
{
	void	*img_ptr;
	char	*img_pixels_ptr;
	int		bits_per_pixel;
	int		endian;
	int		line_len;
}	t_img;


typedef struct s_pos
{
	int				x;
	int				y;
	int				z;
	int				color;
	struct s_pos	*down;
	struct s_pos	*right;
	struct s_pos	*next;
}	t_pos;

typedef struct s_data
{
	void	*ptr;
	void	*win;
	t_img	img;
	t_pos	*list;
}	t_data;


void	free_tab(char **tab);
void	free_lst(t_pos *lst);
t_pos	*add_point_to_lst(t_pos *lst, int a, int b, char *seg);
t_pos	*create_list_pos(int fd);
char	**ft_super_split(char *str, char *charset);
t_pos	*last_elem(t_pos **list);
float	gap_p(t_pos **list, char c);

void	put_square_10(t_img *img, int x, int y, int color);
void	put_list_into_pixels(t_pos **list, t_img img);


void	put_my_pixel(t_img *img, int x, int y, int color);
void	full_spread(t_pos **list);
void	center_points_in_image(t_pos **list);
void	set_color(t_pos **list, int fd);
void	draw_the_map(t_pos **list, t_img image);
int	comma_is_in(char *s);
int	comma_pos(char *s);
int	hexachar_to_digit(char c);
unsigned int	hexastr_to_int(char *s);



# endif