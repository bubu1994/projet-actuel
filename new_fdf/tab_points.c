/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_points.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gebuqaj <gebuqaj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 08:56:57 by gebuqaj           #+#    #+#             */
/*   Updated: 2024/02/09 13:33:08 by gebuqaj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	*process_line(char *line, int size)
{
	char	**splitted;
	int		*res;
	int		i;

	res = malloc(sizeof(int) * size);
	if (!res)
		return (NULL);
	splitted = ft_split(line, ' ');
	i = 0;
	while (i < size)
	{
		res[i] = ft_atoi(splitted[i]);
		i++;
	}
	free_tableau(splitted);
	return (res);
}

int	**tab_points(char *file, t_axes axes)
{
	int		**res;
	char	*line;
	int		i;
	int		fd;

	res = malloc(sizeof(int *) * (axes.y_extrem + 1));
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
		res[i] = process_line(line, axes.x_extrem);
		free(line);
		i++;
	}
	res[i] = NULL;
	close(fd);
	return (res);
}
/* int main(int argc, char **argv)
{
	t_axes axes = get_width_height(argv[1]);
	int **tab = create_tab(argv[1], axes);
	int i = 0;
	int k;
	while (tab[i] != NULL)
	{
		k = 0;
		while (k < axes.x_extrem)
		{
			printf(" |%d| ", tab[i][k]);
			k++;
		}
		printf("\n");
		i++;
	}
	free_tableau_int(tab);
	return (0);
} */