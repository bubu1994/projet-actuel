/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gebuqaj <gebuqaj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 10:37:10 by gebuqaj           #+#    #+#             */
/*   Updated: 2024/03/25 13:35:59 by gebuqaj          ###   ########.fr       */
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
	bool		is_full;
	bool		is_dead;
	int			has_eaten_times;
	int			must_eat_times;
	t_fork		*first_fork;
	t_fork		*second_fork;
	t_data		*data;
	pthread_mutex_t	eat_lock;
}	t_philo;

struct s_data
{
	int		philo_nb;
	int		die_time;
	int		eat_time;
	int		sleep_time;
	int		must_eat_times;
	size_t	start_timestamp;
	bool	all_full;
	bool	one_died;
	bool	all_ready;
	t_fork	*forks;
	t_philo	*philos;
	pthread_mutex_t	begin_lock;
	pthread_mutex_t	full_lock;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	dead_lock;
};

long	ft_atol(const char *str);
void	destroy_mutexes_and_free(t_data *le_diner);
size_t	get_time_in_milliseconds(void);
void	ft_usleep(size_t milliseconds, t_philo *filo);
size_t	timestp(t_data *data);


bool	args_are_ok(char **argv);
t_data	*init_diner(char **argv);
void	*routine(void *arg);
void	print_action(t_philo *filo, char *s);
void	status_check(int status);
void	set_bool(pthread_mutex_t *mutex, bool *mybool, bool res);
bool	get_bool(pthread_mutex_t *mutex, bool *mybool);
void	wait_all_threads(t_data *data);
void	sleep_and_may_die(size_t dietime, t_data *data);



#endif