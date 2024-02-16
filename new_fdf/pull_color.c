/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pull_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gentian <gentian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 12:39:05 by gebuqaj           #+#    #+#             */
/*   Updated: 2024/02/12 10:51:45 by gentian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	comma_is_in(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == ',')
			return (1);
		i++;
	}
	return (0);
}

int	comma_pos(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && s[i] != ',')
		i++;
	return (i);
}

int	hexachar_to_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	else if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	else if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	else
		return -1;
}

unsigned int	hexastr_to_int(char *s)
{
	unsigned int	res;
	int				digit;

	res = 0;
	if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X'))
		s = s + 2;
	while (*s)
	{
		digit = hexachar_to_digit(*s);
		if (digit == -1)
		{
			perror("Invalid color");
			exit(1);
		}
		res = res * 16 + digit;
		s++;
	}
	return (res);
}

unsigned int	pull_color(char	*s)
{
	unsigned int	color;

	color = COLOR_DEFAULT;
	if (comma_is_in(s))
		color = hexastr_to_int(s + comma_pos(s) + 1);
	return (color);
}

/* 
int	main(int argc, char **argv)
{
	t_axes axes = get_width_height(argv[1]);
	char ***tab = array_of_points(argv[1], axes);
	int x = 1;
	int y = 1;

	printf("%d\n", pull_color(tab[y][x]));
	free_3d(tab);
	return (0);
} */