/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gebuqaj <gebuqaj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 10:36:01 by gebuqaj           #+#    #+#             */
/*   Updated: 2024/03/25 13:54:39 by gebuqaj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*(takes forks), eats, sleeps, thinks
repeat*/

void	check_filos(t_philo *filos)
{
	int		i;
	bool	one_isnot_full;

	i = 0;
	one_isnot_full = false;
	while (i < filos->data->philo_nb)
	{
		if (filos[i].is_full == false)
			one_isnot_full = true;
		i++;
	}
	if (one_isnot_full == false)
		set_bool(&filos->data->full_lock, &filos->data->all_full, true);
}

void	*monitoring(void *arg)
{
	t_philo	*filos;

	filos = (t_philo *)arg;
	while (1)
	{
		check_filos(filos);
		if (filos->data->all_full || filos->data->one_died)
			break ;
	}
	return (NULL);
}

void	dining(t_data *diner)
{
	pthread_t	monitor;
	t_philo	*les_philos;
	int		i;

	les_philos = diner->philos;
	status_check(pthread_create(&monitor, NULL, monitoring, (void *)les_philos));
	i = -1;
	while (++i < diner->philo_nb)
		status_check(pthread_create(&les_philos[i].thread, NULL, routine, (void *)&les_philos[i]));
	set_bool(&diner->begin_lock, &diner->all_ready, true);
	diner->start_timestamp = get_time_in_milliseconds();
	status_check(pthread_join(monitor, NULL));
	i = -1;
	while (++i < diner->philo_nb)
		status_check(pthread_join(les_philos[i].thread, NULL));
}

int	main(int argc, char **argv)
{
	t_data	*le_diner;

	if (argc < 5 || argc > 6 || args_are_ok(argv + 1) == false
		|| ft_atol(argv[1]) < 1)
	{
		printf("Arguments invalides\n");
		return (0);
	}
	le_diner = init_diner(argv);
	dining(le_diner);
	if (le_diner->all_full)
		printf("%zu All philos are full\n", timestp(le_diner));
	destroy_mutexes_and_free(le_diner);
	return (0);
}

/*
Des qu'une variable peut etre changee ou LUE par plusieurs threads, il faut lock
*/