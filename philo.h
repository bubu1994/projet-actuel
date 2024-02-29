/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gebuqaj <gebuqaj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 10:37:10 by gebuqaj           #+#    #+#             */
/*   Updated: 2024/02/29 17:06:04 by gebuqaj          ###   ########.fr       */
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
# include <stdbool.h>
# include <limits.h>

typedef struct s_data t_data;

typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				id_fork;
}	t_fork;

typedef struct t_philo
{
	pthread_t	thread;
	int			id;
	long		last_meal_timestamp;
	bool		full;
	t_fork		*left_fork;
	t_fork		*right_fork;
	t_data		*data;
}	t_philo;

struct s_data
{
	int		philo_nb;
	int		forks_nb;
	int		die_time;
	int		eat_time;
	int		sleep_time;
	int		must_eat_times;
	int		start_timestamp;
	bool	end_simulaton;
	t_fork	*forks;
	t_philo	*philos;
};

int	ft_atoi(const char *str);

#endif