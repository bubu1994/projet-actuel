/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gebuqaj <gebuqaj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 10:36:01 by gebuqaj           #+#    #+#             */
/*   Updated: 2024/02/29 17:14:23 by gebuqaj          ###   ########.fr       */
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
	printf("Philo %d says hi\n", philo.id);
	return (NULL);
}

void	check_status(int status)
{
	if (status != 0)
	{
		printf("Error creating or joining thread\n");
		exit(1);
	}
	return ;
}

int	main(int argc, char **argv)
{
	t_data		data;
	pthread_t	*tab_th;
	t_philo		*tab_philo;
	int			i;
	int			status;

	if (argc < 5 || argc > 6)
		return (0);
	i = 0;
	data = init_data(argv);
	tab_th = malloc(sizeof(pthread_t) * data.philo_nb);
	tab_philo = malloc(sizeof(t_philo) * data.philo_nb);
	if (!tab_th || !tab_philo)
		return (1);
	while (i < data.philo_nb)
	{
		tab_philo[i].id = i + 1;
		status = pthread_create(&tab_th[i], NULL, my_func, (void *)&tab_philo[i]);
		check_status(status);
		i++;
	}
	i = 0;
 	while (i < data.philo_nb)
	{
		status = pthread_join(tab_th[i], NULL);
		check_status(status);
		i++;
	}
	free(tab_th);
	free(tab_philo);
	printf("All philos said hi\n");
	return (0);
}