/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gebuqaj <gebuqaj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 10:36:01 by gebuqaj           #+#    #+#             */
/*   Updated: 2024/03/06 12:35:21 by gebuqaj          ###   ########.fr       */
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

/*thinks, (takes forks), eats, sleeps
repeat*/

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

	print_data(le_diner);
	destroy_mutexes_and_free(le_diner);
	return (0);
}