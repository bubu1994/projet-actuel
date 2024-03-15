/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gebuqaj <gebuqaj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 10:36:01 by gebuqaj           #+#    #+#             */
/*   Updated: 2024/03/15 11:19:00 by gebuqaj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*(takes forks), eats, sleeps, thinks
repeat*/

void	check_fullness(t_philo *filos)
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
		filos->data->the_end = true;
}

void	*monitoring(void *arg)
{
	t_philo	*filos;

	filos = (t_philo *)arg;
	while (1)
	{
		check_fullness(filos);
		if (filos->data->the_end)
			break;
	}
	return (NULL);
}

void	dining(t_data diner)
{
	pthread_t	monitor;
	t_philo	*les_philos;
	int		status;
	int		i;

	les_philos = diner.philos;
	status = pthread_create(&monitor, NULL, monitoring, (void *)les_philos);
	if (status != 0)
	{
		printf("Erreur creation thread/monitor\n");
		return ;
	}
	i = -1;
	while (++i < diner.philo_nb)
	{
		status = pthread_create(&les_philos[i].thread, NULL, routine, (void *)&les_philos[i]);
		if (status != 0)
		{
			printf("Erreur creation thread/philo %d\n", i + 1);
			return ;
		}
	}
	status = pthread_join(monitor, NULL);
	if (status != 0)
	{
		printf("Erreur attente thread/monitor\n");
		return ;
	}
	i = -1;
	while (++i < diner.philo_nb)
	{
		status = pthread_join(les_philos[i].thread, NULL);
		if (status != 0)
		{
			printf("Erreur attente du thread/philo %d\n", i + 1);
			return ;
		}
	}
}

int	main(int argc, char **argv)
{
	t_data	le_diner;

	if (argc < 5 || argc > 6 || args_are_ok(argv + 1) == false
		|| ft_atol(argv[1]) < 1)
	{
		printf("Arguments invalides\n");
		return (0);
	}
	le_diner = init_diner(argv);
	dining(le_diner);
	destroy_mutexes_and_free(le_diner);
	return (0);
}