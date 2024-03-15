/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gebuqaj <gebuqaj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 09:42:10 by gebuqaj           #+#    #+#             */
/*   Updated: 2024/03/15 11:06:32 by gebuqaj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_philo *filo, char *s)
{
	pthread_mutex_lock(&filo->data->print_lock);
	printf("%zu %d %s", timestp(filo), filo->id, s);
	pthread_mutex_unlock(&filo->data->print_lock);
}

static void	eats(t_philo *filo)
{
	pthread_mutex_lock(&filo->first_fork->fork);
	print_action(filo, "has taken a fork\n");
	pthread_mutex_lock(&filo->second_fork->fork);
	print_action(filo, "has taken a fork\n");
	print_action(filo, "is eating\n");
	ft_usleep(filo->data->eat_time);
	pthread_mutex_lock(&filo->lock);
	filo->has_eaten_times++;
	filo->last_meal_timestamp = timestp(filo);
	if (filo->has_eaten_times == filo->must_eat_times)
		filo->is_full = true;
	pthread_mutex_unlock(&filo->lock);
	pthread_mutex_unlock(&filo->first_fork->fork);
	pthread_mutex_unlock(&filo->second_fork->fork);
}

void	sleeps(t_philo *filo)
{
	print_action(filo, "is sleeping\n");
	ft_usleep(filo->data->sleep_time);
}

void	thinks(t_philo *filo)
{
	print_action(filo, "is thinking\n");
}

void	*routine(void *arg)
{
	t_philo		*filo;

	filo = (t_philo *)arg;
	while (!filo->data->the_end)
	{
		eats(filo);
		sleeps(filo);
		thinks(filo);
	}
	return (NULL);
}