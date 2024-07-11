/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_datas.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 19:39:05 by jlebard           #+#    #+#             */
/*   Updated: 2024/06/30 19:39:05 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	assign_forks(t_philo *philos, t_dinner *dinner)
{
	int	i;

	i = 0;
	while (i < dinner->rules.nb_of_philo)
	{
		if (philos[i].id_philo == dinner->rules.nb_of_philo && \
		philos[i].id_philo % 2 == 1)
		{
			philos[i].first_fork = &(dinner->forks[philos[i].id_philo]);
			philos[i].second_fork = &(dinner->forks[philos[i].id_philo - 1]);
		}
		else if (philos[i].id_philo % 2 == 1)
		{
			philos[i].first_fork = &(dinner->forks[philos[i].id_philo]);
			philos[i].second_fork = &(dinner->forks[philos[i].id_philo - 1]);
		}
		else
		{
			philos[i].first_fork = &(dinner->forks[philos[i].id_philo - 1]);
			philos[i].second_fork = &(dinner->forks[philos[i].id_philo]);
		}
	}
}

static void	init_philos(t_dinner *dinner)
{
	int		i;
	t_philo	*philos;
	
	i = 0;
	philos = malloc(sizeof(t_philo) * dinner->rules.nb_of_philo);
	if (philos == NULL)
	{
		free_dinner(dinner);
		exit_error("Pb Malloc.\n");
	}
	dinner->philos = philos;
	while (i < dinner->rules.nb_of_philo)
	{
		philos[i].full = 0;
		philos[i].nb_of_meals = 0;
		philos[i].atable = &(dinner->rules);
		philos[i].id_philo = ++i;
	}
	assign_forks(dinner->philos, dinner);
}

void	init_dinner(t_dinner *dinner)
{
	int	i;

	i = 0;
	dinner->rules.finish = 0;
	dinner->rules.threads_ready = 0;
	dinner->forks = malloc(sizeof(t_fork) * dinner->rules.nb_of_philo);
	handle_mutex(&(dinner->rules.rules_mtx), CREATE);
	handle_mutex(&(dinner->rules.write_mutex), CREATE);
	if (dinner->forks = NULL)
		exit_error("Pb Malloc.\n");
	while (i < dinner->rules.nb_of_philo)
	{
		handle_mutex(&(dinner->forks[i].mtx_fork), CREATE);
		dinner->forks[i].id_fork = ++i;
	}
	init_philos(dinner);
}
