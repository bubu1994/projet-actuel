/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gebuqaj <gebuqaj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 10:36:01 by gebuqaj           #+#    #+#             */
/*   Updated: 2024/03/14 12:56:40 by gebuqaj          ###   ########.fr       */
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
size_t	timestp(t_philo *filo)
{
	return (get_time_in_milliseconds() - filo->data->start_timestamp);
}

void	print_action(t_philo *filo, char *s)
{
	pthread_mutex_lock(&filo->data->print_lock);
	printf("%zu %d %s", timestp(filo), filo->id, s);
	pthread_mutex_unlock(&filo->data->print_lock);
}

static void	eats(t_philo *filo)
{
	pthread_mutex_lock(&filo->first_fork->fork);
	printf("%zu %d has taken fork %d\n",
		timestp(filo), filo->id, filo->first_fork->id_fork);
	pthread_mutex_lock(&filo->second_fork->fork);
	printf("%zu %d has taken fork %d\n",
		timestp(filo),filo->id, filo->second_fork->id_fork);
	printf("%zu %d is eating\n",
		timestp(filo), filo->id);
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
	while (1)
	{
		eats(filo);
		sleeps(filo);
		thinks(filo);
	}
	return (NULL);
}

void	dining(t_data diner)
{
	int		i;
	t_philo	*les_philos;
	int		status;

	les_philos = diner.philos;
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