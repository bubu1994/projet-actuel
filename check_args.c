/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gebuqaj <gebuqaj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:53:42 by gebuqaj           #+#    #+#             */
/*   Updated: 2024/03/25 10:38:09 by gebuqaj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	args_are_positive_int(char **argv)
{
	int		i;
	long	n;

	i = 0;
	while (argv[i])
	{
		n = ft_atol(argv[i]);
		if (n > INT_MAX || n < 0)
			return (0);
		i++;
	}
	return (1);
}

int	args_are_digits(char **argv)
{
	int	i;
	int	k;

	if (*argv == NULL || **argv == '\0')
		return (0);
	i = 0;
	while (argv[i])
	{
		k = 0;
		if (argv[i][k] == '-' || argv[i][k] == '+')
			k++;
		if (argv[i][k] == '\0')
			return (0);
		while (argv[i][k])
		{
			if (argv[i][k] > '9' || argv[i][k] < '0')
				return (0);
			k++;
		}
		i++;
	}
	return (1);
}

bool	args_are_ok(char **argv)
{
	if (args_are_digits(argv) && args_are_positive_int(argv))
		return (true);
	else
		return (false);
}
