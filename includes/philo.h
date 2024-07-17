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

# define GREEN "\e[0;32m"
# define BLUE "\e[0;34m"
# define RED "\e[0;31m"
# define RESET "\e[0m"

//enum pour les mutex

typedef enum	e_mutex_code
{
	CREATE,
	DESTROY,
	LOCK,
	UNLOCK,
}	t_mutex_code;

typedef enum	e_thread_code
{
	CREATE,
	JOIN,
	DETACH,
}	t_thread_code;

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
	int				eaten_nb;
	long			time_since_last_meal;	
	bool			full;
	pthread_mutex_t	philo_mtx;
	pthread_t		philo_thread;
	t_fork			*first_fork;
	t_fork			*second_fork;
	t_dinner		*dinner;
}	t_philo;

//structure pour le dîner
typedef struct	s_dinner
{
	int				nb_philo;
	int				nb_meals;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	bool			finished;
	bool			threads_ready;
	pthread_mutex_t	dinner_mtx;
	t_fork			*forks;
	t_philo			*philos;
}	t_dinner;

//utils
void	ft_putstr_fd(char *s, int fd);
int		handle_mutex(pthread_mutex_t *mtx, t_mutex_code code);
int		handle_thread(pthread_t *th, void *(*f)(void *), void *data,
					t_thread_code code);

//parsing
int		parse(t_dinner *dinner, char **argv);

//initialisation des structures
int		init_data(t_dinner *dinner);

//simulation
int		begin_simulation(t_dinner *dinner);

//main

#endif
