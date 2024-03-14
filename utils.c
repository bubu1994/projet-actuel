/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gebuqaj <gebuqaj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 10:45:11 by gebuqaj           #+#    #+#             */
/*   Updated: 2024/03/14 10:38:44 by gebuqaj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(const char *str)
{
	int		i;
	int		sign;
	long	nb;

	i = 0;
	nb = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10;
		nb = nb + (str[i] - 48);
		i++;
	}
	return (nb * sign);
}

size_t	get_time_in_milliseconds(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		printf("Erreur gettimeofday\n");
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

size_t	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_time_in_milliseconds();
	while ((get_time_in_milliseconds() - start < milliseconds))
		usleep(500);
	return (0);
}

void	destroy_mutexes_and_free(t_data le_diner)
{
	int	i;

	i = 0;
	while (i < le_diner.philo_nb)
	{
		pthread_mutex_destroy(&le_diner.forks[i].fork);
		i++;
	}
	free(le_diner.forks);
	free(le_diner.philos);
}
