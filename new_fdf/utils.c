/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gebuqaj <gebuqaj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 09:53:48 by gebuqaj           #+#    #+#             */
/*   Updated: 2024/02/09 14:53:48 by gebuqaj          ###   ########.fr       */
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
		perror("Erreur ouverture fichier");
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
	tab = ft_split(line, ' ');
	res.x_extrem = size_tableau(tab);
	free_tableau(tab);
	y = 0;
	while (line != NULL)
	{
		y++;
		free(line);
		line = get_next_line(fd);
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
		res[i] = ft_split(line, ' ');
		free(line);
		i++;
	}
	res[i] = NULL;
	close(fd);
	return (res);
}
