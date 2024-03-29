/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gebuqaj <gebuqaj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:31:05 by gebuqaj           #+#    #+#             */
/*   Updated: 2024/03/25 13:19:41 by gebuqaj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_fork	*init_forks(int	nb_philos)
{
	t_fork	*res;
	int		status;
	int		i;

	i = 0;
	res = malloc(sizeof(t_fork) * nb_philos);
	if (!res)
		return (NULL);
	while (i < nb_philos)
	{
		res[i].id_fork = i;
		status = pthread_mutex_init(&res[i].fork, NULL);
		if (status != 0)
		{
			printf("Erreur initialisation du mutex/fork %d\n", i);
			return (NULL);
		}
		i++;
	}
	return (res);
}

void	assign_forks(t_philo *res, t_data diner, int i)
{
	res[i].first_fork = &diner.forks[i];
	if (res[i].id == diner.philo_nb)
		res[i].second_fork = &diner.forks[0];
	else
		res[i].second_fork = &diner.forks[i + 1];
	if (res[i].id % 2 == 0)
	{
		if (res[i].id == diner.philo_nb)
			res[i].first_fork = &diner.forks[0];
		else
			res[i].first_fork = &diner.forks[i + 1];
		res[i].second_fork = &diner.forks[i];
	}
}

t_philo	*init_philos(t_data *diner)
{
	t_philo	*res;
	int		i;

	i = -1;
	res = malloc(sizeof(t_philo) * diner->philo_nb);
	if (!res)
		return (NULL);
	while (++i < diner->philo_nb)
	{
		res[i].id = i + 1;
		res[i].is_full = false;
		res[i].is_dead = false;
		res[i].must_eat_times = diner->must_eat_times;
		res[i].has_eaten_times = 0;
		res[i].last_meal_timestamp = diner->start_timestamp;
		assign_forks(res, *diner, i);
		res[i].data = diner;
		pthread_mutex_init(&res[i].eat_lock, NULL);
	}
	return (res);
}

t_data	*init_diner(char **argv)
{
	t_data	*res;

	res = malloc(sizeof(t_data));
	if (!res)
		return (NULL);
	res->philo_nb = (int)ft_atol(argv[1]);
	res->die_time = (int)ft_atol(argv[2]);
	res->eat_time = (int)ft_atol(argv[3]);
	res->sleep_time = (int)ft_atol(argv[4]);
	if (argv[5])
		res->must_eat_times = (int)ft_atol(argv[5]);
	else
		res->must_eat_times = -41;
	res->all_full = false;
	res->one_died = false;
	res->all_ready = false;
	res->forks = init_forks(res->philo_nb);
	res->philos = init_philos(res);
	res->start_timestamp = get_time_in_milliseconds();
	pthread_mutex_init(&res->begin_lock, NULL);
	pthread_mutex_init(&res->print_lock, NULL);
	pthread_mutex_init(&res->full_lock, NULL);
	pthread_mutex_init(&res->dead_lock, NULL);
	return (res);
}
