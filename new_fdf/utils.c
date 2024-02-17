/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gebuqaj <gebuqaj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 09:53:48 by gebuqaj           #+#    #+#             */
/*   Updated: 2024/02/16 16:49:39 by gebuqaj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_tableau(char **tab)
{
	int	i;

	i = 0;
	if (tab == NULL)
		return ;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_3d(char ***array)
{
	int	i;

	i = 0;
	if (array == NULL)
		return ;
	while (array[i])
	{
		free_tableau(array[i]);
		i++;
	}
	free(array);
}

int	size_tableau(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
		i++;
	return (i);
}

void	fd_open_error(int fd)
{
	if (fd == -1)
	{
		perror("Erreur fichier");
		exit(1);
	}
	return ;
}

t_axes	get_width_height(char *file)
{
	t_axes	res;
	char	*line;
	char	**tab;
	int		y;
	int		fd;

	fd = open(file, O_RDONLY);
	fd_open_error(fd);
	line = get_next_line(fd);
	tab = ft_super_split(line, " \n");
	res.x_extrem = size_tableau(tab);
	free_tableau(tab);
	y = 0;
	while (line != NULL)
	{
		y++;
		free(line);
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		tab = ft_super_split(line, " \n");
		res.temp_x = size_tableau(tab);
		if (res.temp_x != res.x_extrem)
		{
			perror("Erreur fichier");
			close(fd);
			free(line);
			exit(1);
		}
		free_tableau(tab);
	}
	res.y_extrem = y;
	close(fd);
	return (res);
}

char	***array_of_points(char *file, t_axes axes)
{
	char	***res;
	char	*line;
	int		i;
	int		fd;

	res = malloc(sizeof(char **) * (axes.y_extrem + 1));
	if (!res)
		return (NULL);
	fd = open(file, O_RDONLY);
	fd_open_error(fd);
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		res[i] = ft_super_split(line, " \n");
		free(line);
		i++;
	}
	res[i] = NULL;
	close(fd);
	return (res);
}

uint32_t	degrade_color(int a, int b, int i, int steps)
{
	t_color	dif;
	t_color	new;
	float	ratio;

	ratio = (float)i / (float)steps;
	dif.r = ((a >> 24) & 0xFF) - ((b >> 24) & 0xFF);
	dif.g = ((a >> 16) & 0xFF) - ((b >> 16) & 0xFF);
	dif.b = ((a >> 8) & 0xFF) - ((b >> 8) & 0xFF);
	dif.a = (a & 0xFF) - (b & 0xFF);
	new.r = ((a >> 24) & 0xFF) - (dif.r * ratio);
	new.g = ((a >> 16) & 0xFF) - (dif.g * ratio);
	new.b = ((a >> 8) & 0xFF) - (dif.b * ratio);
	new.a = (a & 0xFF) - dif.a * ratio;
	return ((new.r << 24) | (new.g << 16) | (new.b << 8) | new.a);
}