/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gebuqaj <gebuqaj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 10:36:01 by gebuqaj           #+#    #+#             */
/*   Updated: 2024/02/28 12:07:47 by gebuqaj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	init_data(char **argv)
{
	t_data	res;

	res.philo_nb = ft_atoi(argv[1]);

	return (res);
}

void	*my_func(void *arg)
{
	t_philo philo;

	philo = *(t_philo *)arg;
	printf("Philo %d says hello\n", philo.id);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_data		data;
	pthread_t	*tab_th;
	t_philo		*tab_philo;
	int			i;
	int			status;

	(void)argc;
	i = 1;
	data = init_data(argv);
	tab_th = malloc(sizeof(pthread_t) * data.philo_nb);
	tab_philo = malloc(sizeof(t_philo) * data.philo_nb);
	if (!tab_th || !tab_philo)
		return (1);
	while (i <= data.philo_nb)
	{
		tab_philo[i].id = i;
		status = pthread_create(&tab_th[i], NULL, my_func, (void *)&tab_philo[i]);
		if (status != 0)
		{
			printf("Error creating thread\n");
			return (1);
		}
		i++;
	}
	i = 1;
	while (i <= data.philo_nb)
	{
		status = pthread_join(tab_th[i], NULL);
		if (status != 0)
		{
			printf("Error joining thread %d\n", i);
			return (1);
		}
		i++;
	}
	free(tab_th);
	free(tab_philo);
	printf("All philos said hello\n");
	return (0);
}