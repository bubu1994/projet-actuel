/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_of_points.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gebuqaj <gebuqaj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 13:58:56 by gebuqaj           #+#    #+#             */
/*   Updated: 2024/02/09 14:25:51 by gebuqaj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
