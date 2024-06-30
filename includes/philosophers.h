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

//struct pour les philos
typedef struct s_philos
{
	int	id_philo;
}	t_philo;

// struct pour les forks
typedef struct s_forks
{
	int				id_fork;
	p_thread_mutex	fork;
}	t_fork;

// struct pour les règles 
typedef struct s_rules
{
	int			nb_of_philo;
	long		die_time;
	long		eat_time;
	long		sleep_time;
	int			must_eat;
	t_fork		*forks;
	t_philos	*philos;
}	t_rules;

// erreurs et free
void	exit_error(char *s);

#endif