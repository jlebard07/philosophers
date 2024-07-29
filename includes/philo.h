/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:08:41 by jlebard           #+#    #+#             */
/*   Updated: 2024/07/11 16:08:41 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>
# include <limits.h>
# include <errno.h>

# define G "\e[0;32m"
# define B "\e[0;34m"
# define R "\e[0;31m"
# define RST "\e[0m"

//enum pour les mutex
typedef enum	e_mutex_code
{
	INIT,
	DESTROY,
	LOCK,
	UNLOCK,
}	t_mutex_code;

//enum pour les threads
typedef enum	e_thread_code
{
	CREATE,
	JOIN,
	DETACH,
}	t_thread_code;

//enum pour  les actions
typedef enum	e_action_code
{
	EATS,
	TAKE_FIRST_FORK,
	TAKE_SCND_FORK,
	SLEEPS,
	THINKS,
	DEAD,
}	t_action_code;

typedef struct s_dinner t_dinner;

//structure pour les forks
typedef struct	s_fork
{
	int				fork_id;
	pthread_mutex_t	fork_mtx;
}	t_fork;

//structure pour les philos
typedef struct	s_philo
{
	int				philo_id;
	long			eaten_nb;
	long			last_meal_time;	
	bool			full;
	bool			dead;
	pthread_mutex_t	philo_mtx;
	pthread_t		philo_thread;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
	t_dinner		*dinner;
}	t_philo;

//structure pour le dîner
typedef struct	s_dinner
{
	int				nb_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			start_time;
	long			nb_meals;
	long			ready_nb;
	bool			finished;
	pthread_t		monitor;
	pthread_mutex_t	dinner_mtx;
	pthread_mutex_t write_mtx;
	t_fork			*forks;
	t_philo			*philos;
}	t_dinner;

//utils
int		handle_mutex(pthread_mutex_t *mtx, t_mutex_code code);
int		handle_thread(pthread_t *th, void *(*f)(void *), void *data,
					t_thread_code code);
void	set_bool(bool *dest, bool b, pthread_mutex_t *mtx);
bool	get_bool(bool *to_get, pthread_mutex_t *mtx);
void	set_long(long *dest, long l, pthread_mutex_t *mtx);
long	get_long(long *to_get, pthread_mutex_t *mtx);
void	inc_long(long *dest, pthread_mutex_t *mtx);
long	get_time(bool second, bool mili);
void	precise_usleep(long time_to_sleep);
void	write_action(t_action_code code, t_philo *philo);

//parsing
int		parse(t_dinner *dinner, char **argv);

//initialisation des structures
int		init_data(t_dinner *dinner);

//simulation
void	begin_simulation(t_dinner *dinner);
void	*actual_dinner(void *data);
void	*f_monitor(void	*data);
void	*im_so_lonely(void *data);
bool	end_simulation(t_dinner *dinner);

//main

#endif
