/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gebuqaj <gebuqaj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 09:42:10 by gebuqaj           #+#    #+#             */
/*   Updated: 2024/03/25 14:01:36 by gebuqaj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_philo *filo, char *s)
{
	pthread_mutex_lock(&filo->data->print_lock);
	printf("%zu %d %s", timestp(filo->data), filo->id, s);
	pthread_mutex_unlock(&filo->data->print_lock);
}

static void	eats(t_philo *filo)
{
	pthread_mutex_lock(&filo->first_fork->fork);
	print_action(filo, "has taken a fork\n");
	pthread_mutex_lock(&filo->second_fork->fork);
	print_action(filo, "has taken a fork\n");	
	print_action(filo, "is eating\n");
	pthread_mutex_lock(&filo->eat_lock);
	filo->has_eaten_times++;
	filo->last_meal_timestamp = timestp(filo->data);
	if (filo->has_eaten_times == filo->must_eat_times)
		filo->is_full = true;
	ft_usleep(filo->data->eat_time, NULL);
	pthread_mutex_unlock(&filo->eat_lock);
	pthread_mutex_unlock(&filo->first_fork->fork);
	pthread_mutex_unlock(&filo->second_fork->fork);
}

void	sleeps(t_philo *filo)
{
	print_action(filo, "is sleeping\n");
	ft_usleep(filo->data->sleep_time, filo);
}

void	thinks(t_philo *filo)
{
	print_action(filo, "is thinking\n");
	ft_usleep(1, filo);
}

void	*routine(void *arg)
{
	t_philo		*filo;

	filo = (t_philo *)arg;
	wait_all_threads(filo->data);
	if (filo->id % 2 == 0)
		usleep(1);
	while (1)
	{
		eats(filo);
		if (get_bool(&filo->data->full_lock, &filo->data->all_full))
			break ;
		sleeps(filo);
		if (get_bool(&filo->data->full_lock, &filo->data->all_full))
			break ;
		thinks(filo);
	}
	return (NULL);
}