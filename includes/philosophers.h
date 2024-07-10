/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:02:17 by jlebard           #+#    #+#             */
/*   Updated: 2024/06/28 16:02:17 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>
# include <limits.h>
# include <errno.h>

//énumération fonctions mutex
typedef enum e_mtxcode
{
	LOCK,
	UNLOCK,
	CREATE,
	DESTROY,
}	t_mtxcode;

//énumération fonctinos threads
typedef enum e_thcode
{
	CREATE,
	JOIN,
	DETACH,
}	t_thcode;

//struct pour les philos
typedef struct s_philos
{
	int			id_philo;
	int			nb_of_meals;
	bool		full;
	pthread_t	th_philo;
	t_fork		*first_fork;
	t_fork		*second_fork;
	t_rules		*atable;
}	t_philo;

// struct pour les forks
typedef struct s_forks
{
	int				id_fork;
	pthread_mutex_t	mtx_fork;
}	t_fork;

// struct règles
typedef struct	s_rules
{
	int			nb_of_philo;
	long		die_time;
	long		eat_time;
	long		sleep_time;
	int			must_eat;
	bool		threads_ready;
	pthread_mutex_t	rules_mtx;
}	t_rules;

// struct global 
typedef struct s_dinner
{
	t_rules		rules;
	t_fork		*forks;
	t_philo		*philos;
}	t_dinner;

//fonctions threads et mutex
void	handle_mutex(pthread_mutex_t *mutex, t_mtxcode mtxcode);
void	handle_thread(pthread_t *thread, void *(*f)(void*), void *arg,
						t_thcode thcode);

// erreurs et free
void	exit_error(char *s);
void	free_dinner(t_dinner *dinner);

//getters and setters
void	set_bool(pthread_mutex_t mtx, bool *dest, bool value);
bool	get_bool(pthread_mutex_t mtx, bool *value);
void	set_long(pthread_mutex_t mtx, long *dest, long value);
long	get_long(pthread_mutex_t mtx, long *value);

// parsing
void	parse(t_rules rules, char **argv);

//main
int		main(int argc, char **argv);

//inits
void	init_dinner(t_dinner *dinner);

//simulation
void	time_to_eat(t_dinner *dinner);

#endif
