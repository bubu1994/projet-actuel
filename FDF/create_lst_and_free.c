/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_lst_and_free.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gebuqaj <gebuqaj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 12:53:51 by gebuqaj           #+#    #+#             */
/*   Updated: 2024/02/08 11:19:45 by gebuqaj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/fdf.h"

void	free_tab(char **tab)
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

void	free_lst(t_pos *lst)
{
	t_pos	*temp;

	while (lst)
	{
		temp = lst;
		lst = lst->next;
		free(temp);
	}
}

t_pos	*add_point_to_lst(t_pos *lst, int a, int b, char *seg)
{
	t_pos	*elem;
	t_pos	*dernier;

	elem = malloc(sizeof(t_pos));
	if (!elem)
		return (NULL);
	elem->x = a;
	elem->y = b;
	elem->z = ft_atoi(seg);
	if (comma_is_in(seg))
		elem->color = hexastr_to_int(seg + comma_pos(seg) + 1);
	else
		elem->color = COLOR_DEFAULT;
	elem->next = NULL;
	if (!lst)
		return (elem);
	dernier = lst;
	while (dernier->next != NULL)
		dernier = dernier->next;
	dernier->next = elem;
	return (lst);
}

void	set_downs_and_rights(t_pos **list)
{
	t_pos	*scan;
	t_pos	*next_down;

	scan = *list;
	next_down = *list;
	while (next_down->y == scan->y)
		next_down = next_down->next;
	while (next_down != NULL)
	{
		scan->down = next_down;
		scan = scan->next;
		next_down = next_down->next;
	}
	while (scan)
	{
		scan->down = NULL;
		scan = scan->next;
	}
	scan = *list;
	while (scan->next != NULL)
	{
		if (scan->y == scan->next->y)
			scan->right = scan->next;
		else
			scan->right = NULL;
		scan = scan->next;
	}
}

void	process_line(char *line, t_pos **lst, int y)
{
	char	**tab;
	int		i;

	i = 0;
	tab = ft_super_split(line, " \n");
	while (tab[i] != NULL)
	{
		*lst = add_point_to_lst(*lst, i, y, tab[i]);
		i++;
	}
	free_tab(tab);
}

t_pos	*create_list_pos(int fd)
{
	t_pos	*lst;
	char	*line;
	int		y;

	y = 0;
	lst = NULL;
	line = get_next_line(fd);
	while (line != NULL)
	{
		process_line(line, &lst, y);
		y++;
		free(line);
		line = get_next_line(fd);
	}
	set_downs_and_rights(&lst);
	return (lst);
}
