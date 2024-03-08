/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gebuqaj <gebuqaj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 10:36:01 by gebuqaj           #+#    #+#             */
/*   Updated: 2024/03/08 16:04:43 by gebuqaj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_data(t_data diner)
{
	int		i;
	t_philo filo;

	i = 0;
	while (i < diner.philo_nb)
	{
		filo = diner.philos[i];
		printf("philo %d, l: %d, r: %d\n", filo.id, filo.first_fork->id_fork, filo.second_fork->id_fork);
		i++;
	}
}

/*(takes forks), eats, sleeps, thinks
repeat*/
bool	is_not_dying(t_philo *filo)
{
	
}

void	*routine(void *arg)
{
	t_philo *filo;

	filo = (t_philo *)arg;
	while (is_not_dying(filo))
	{
		eats(filo);
		sleeps(filo);
		thinks(filo);
	}
	return (NULL);
}

void	start_threads(t_data diner)
{
	int		i;
	t_philo	*les_philos;
	int		status;

	les_philos = diner.philos;
	i = 0;
	while (i < diner.philo_nb)
	{
		status = pthread_create(&les_philos[i].thread, NULL, routine, (void *)&les_philos[i]);
		if (status != 0)
		{
			printf("Erreur creation thread/philo %d\n", i + 1);
			return ;
		}
		i++;
	}
	i = 0;
	while (i < diner.philo_nb)
	{
		status = pthread_join(les_philos[i].thread, NULL);
		if (status != 0)
		{
			printf("Erreur attente du thread/philo %d\n", i + 1);
			return ;
		}
		i++;
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
	start_threads(le_diner);
	destroy_mutexes_and_free(le_diner);
	return (0);
}