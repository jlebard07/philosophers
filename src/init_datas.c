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

static void	assign_forks(t_philo *philo, t_dinner *dinner)
{
	int	i;

	i = 0;
	while (philo[i])
	{
		if (philo[i]->id_philo == dinner->nb_of_philo && \
		philo[i]->id_philo % 2 == 1)
		{
			philo[i]->first_fork = dinner->forks[philo->id_philo];
			philo[i]->second_fork = dinner->forks[philo->id_philo - 1];
		}
		else if (philo[i]->id_philo % 2 == 1)
		{
			philo->first_fork = dinner->fork[philo->id_philo];
			philo->second_fork = dinner->fork[philo->id_philo - 1];
		}
		else
		{
			philo->first_fork = dinner->fork[philo->id_philo - 1];
			philo->second_fork = dinner->fork[philo->id_philo];
		}
	}
}

static void	init_philos(t_dinner *dinner)
{
	int		i;
	t_philo	*philo;
	
	i = 0;
	philo = dinner->philos;
	philo = malloc(sizeof(t_philo) * rules->nb_of_philo);
	if (rules->philo == NULL)
	{
		free(dinner)
		exit_error("Pb Malloc.\n");
	}
	while (rules->philo[i])
	{
		philo[i].full = 0;
		philo[i].nb_of_meal = 0;
		philo[i].id_philo = ++i;
	}
	assign_forks(philo, dinner);
}

void	init_dinner(t_dinner *dinner)
{
	int	i;

	i = 0;
	rules->forks = malloc(sizeof(t_fork) * rules->nb_of_philo);
	if (rules->forks = NULL)
		exit_error("Pb Malloc.\n");
	while (rules->forks[i])
	{
		handle_mutex(&(rules->forks[i].mtx_fork), CREATE);
		rules->forks[i].id_fork = ++i;
	}
	init_philos(dinner);
}
