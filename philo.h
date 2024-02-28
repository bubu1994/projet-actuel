/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gebuqaj <gebuqaj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 10:37:10 by gebuqaj           #+#    #+#             */
/*   Updated: 2024/02/28 11:36:46 by gebuqaj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <string.h>

typedef struct s_data
{
	int	philo_nb;
	int	forks_nb;
	int	die_time;
	int	eat_time;
	int	sleep_time;
	int	must_eaten_times;
}	t_data;

typedef struct t_philo
{
	int			id;
	pthread_t	thread;
}	t_philo;


int	ft_atoi(const char *str);

#endif