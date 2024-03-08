/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gebuqaj <gebuqaj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 10:37:10 by gebuqaj           #+#    #+#             */
/*   Updated: 2024/03/08 16:46:48 by gebuqaj          ###   ########.fr       */
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
	bool		is_dead;
	int			has_eaten_times;
	t_fork		*first_fork;
	t_fork		*second_fork;
	t_data		*data;
}	t_philo;

struct s_data
{
	int		philo_nb;
	int		die_time;
	int		eat_time;
	int		sleep_time;
	int		must_eat_times;
	int		start_timestamp;
	bool	the_end;
	t_fork	*forks;
	t_philo	*philos;
};

long	ft_atol(const char *str);
void	destroy_mutexes_and_free(t_data le_diner);
size_t	get_time_in_ms(void);


bool	args_are_ok(char **argv);
t_data	init_diner(char **argv);



#endif