/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 18:03:42 by jlebard           #+#    #+#             */
/*   Updated: 2024/07/11 18:03:42 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	thinking(t_philo *philo, t_dinner *dinner)
{
	long	t_to_think;

	write_action(THINKS, philo);
	if (dinner->nb_philo % 2 == 1)
	{
		t_to_think = dinner->time_to_eat * 2 - dinner->time_to_sleep;
		if (t_to_think < 0)
			t_to_think = 0;
		precise_usleep((t_to_think / 5) * 1e3);
	}
}

static void	eating(t_philo *philo)
{
	handle_mutex(philo->first_fork, LOCK);
	write_action(TAKE_FIRST_FORK, philo);
	handle_mutex(philo->second_fork, LOCK);
	write_action(TAKE_SCND_FORK, philo);
	write_action(EATS, philo);
	set_long(&philo->last_meal_time, get_time(0, 1), &philo->philo_mtx);
	precise_usleep(philo->dinner->time_to_eat * 1e3);
	philo->eaten_nb++;
	if (philo->dinner->nb_meals != -1
		&& philo->eaten_nb == philo->dinner->nb_meals)
		set_bool(&philo->full, 1, &philo->philo_mtx);
	handle_mutex(philo->first_fork, UNLOCK);
	handle_mutex(philo->second_fork, UNLOCK);
}

void	*actual_dinner(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	set_long(&philo->last_meal_time, get_time(0, 1), &philo->philo_mtx);
	inc_long(&philo->dinner->ready_nb, &philo->dinner->dinner_mtx);
	while (!end_simulation(philo->dinner))
	{
		if (get_bool(&philo->full, &philo->philo_mtx) == 1)
			break ;
		eating(philo);
		set_long(&philo->last_meal_time, get_time(0, 1), &philo->philo_mtx);
		write_action(SLEEPS, philo);
		precise_usleep(philo->dinner->time_to_sleep * 1e3);
		thinking(philo, philo->dinner);
	}
	return (NULL);
}

void	*im_so_lonely(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	handle_mutex(philo->first_fork, LOCK);
	write_action(TAKE_FIRST_FORK, philo);
	precise_usleep(philo->dinner->time_to_die * 1e3);
	write_action(DEAD, philo);
	handle_mutex(philo->first_fork, UNLOCK);
	return (NULL);
}

void	begin_simulation(t_dinner *dinner)
{
	int	i;

	i = 0;
	dinner->start_time = get_time(0, 1);
	if (dinner->nb_philo == 1)
	{
		handle_thread(&dinner->philos[i].philo_thread, im_so_lonely,
			&dinner->philos[i], CREATE);
		handle_thread(&dinner->philos[i].philo_thread, NULL, NULL, JOIN);
	}
	else
	{
		while (i < dinner->nb_philo)
		{
			handle_thread(&dinner->philos[i].philo_thread, actual_dinner,
				&(dinner->philos[i]), CREATE);
			i++;
		}
		handle_thread(&dinner->monitor, f_monitor, dinner, CREATE);
		while (--i >= 0)
			handle_thread(&dinner->philos[i].philo_thread, NULL, NULL, JOIN);
		set_bool(&dinner->finished, 1, &dinner->dinner_mtx);
		handle_thread(&dinner->monitor, NULL, NULL, JOIN);
	}
}
