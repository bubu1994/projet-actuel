/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gebuqaj <gebuqaj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:31:05 by gebuqaj           #+#    #+#             */
/*   Updated: 2024/03/08 14:42:01 by gebuqaj          ###   ########.fr       */
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

t_philo	*init_philos(t_data diner)
{
	t_philo	*res;
	int		i;

	i = -1;
	res = malloc(sizeof(t_philo) * diner.philo_nb);
	if (!res)
		return (NULL);
	while (++i < diner.philo_nb)
	{
		res[i].id = i + 1;
		res[i].full = false;
		res[i].has_eaten_times = 0;
		assign_forks(res, diner, i);
		res[i].data = &diner;
	}
	return (res);
}

t_data	init_diner(char **argv)
{
	t_data	res;

	res.philo_nb = (int)ft_atol(argv[1]);
	res.die_time = (int)ft_atol(argv[2]);
	res.eat_time = (int)ft_atol(argv[3]);
	res.sleep_time = (int)ft_atol(argv[4]);
	if (argv[5])
		res.must_eat_times = (int)ft_atol(argv[5]);
	res.the_end = false;
	res.forks = init_forks(res.philo_nb);
	res.philos = init_philos(res);
	return (res);
}
