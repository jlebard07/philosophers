/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:57:16 by jlebard           #+#    #+#             */
/*   Updated: 2024/07/11 16:57:16 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static t_fork	*find_fork(t_fork *forks, int id)
{
	int	i;

	i = 0;
	while (id != forks[i].fork_id)
		i++;
	return (&forks[i]);
}

static void	assign_forks(t_philo philo, t_fork *forks)
{
	if (philo.philo_id = philo.dinner->nb_meals)
	{
		philo.first_fork = find_fork(forks, 1);
		philo.second_fork = find_fork(forks, philo.philo_id);
	}
	else if (philo.philo_id % 2 == 1)
	{
		philo.first_fork = find_fork(forks, philo.philo_id + 1);
		philo.second_fork = find_fork(forks, philo.philo_id);
	}
	else if (philo.philo_id % 2 == 0)
	{
		philo.first_fork = find_fork(forks, philo.philo_id);
		philo.second_fork = find_fork(forks, philo.philo_id + 1);
	}
}

static int	init_philos(t_dinner *dinner)
{
	int		i;
	t_philo	*philos;

	i = 0;
	philos = dinner->philos;
	while (i < dinner->nb_philo)
	{
		philos[i].philo_id = i + 1;
		philos[i].eaten_nb = 0;
		philos[i].last_meal_time = 0;
		philos[i].full = 0;
		philos[i].dinner = dinner;
		if (handle_mutex(&(philos[i].philo_mtx), CREATE) == -1)
			return (-1);
		assign_forks(philos[i++], dinner->forks);
	}
	return (0);
}

static int	init_fork(t_fork *fork, int nb)
{
	if (handle_mutex(&(fork->fork_mtx), CREATE) == -1)
		return (-1);
	fork->fork_id = nb;
	return (0);
}

int	init_data(t_dinner *dinner)
{
	int	i;
	
	i = 0;
	dinner->finished = 0;
	dinner->threads_ready = 0;
	handle_mutex(&(dinner->dinner_mtx), CREATE);
	handle_mutex(&(dinner->write_mtx), CREATE);
	dinner->forks = malloc(dinner->nb_philo * sizeof(t_fork));
	if (dinner->forks == NULL)
		return (-1);
	while (i < dinner->nb_philo)
	{
		if (init_fork(&(dinner->forks[i++]), i) == -1)
			return (-1);
	}
	dinner->philos = malloc(dinner->nb_philo * sizeof(t_philo));
	if (dinner->philos == NULL)
		return (-1);
	if (init_philos(dinner) == -1)
		return (-1);
	return (0);
}
