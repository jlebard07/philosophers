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

static void	sleeping(t_philo *philo)
{
	write_action(SLEEPS, philo);
	precise_usleep(philo->dinner->time_to_sleep);
}

static void	eating(t_philo *philo)
{
	handle_mutex(philo->first_fork, LOCK);
	write_action(TAKE_FIRST_FORK, philo);
	handle_mutex(philo->second_fork, LOCK);
	write_action(TAKE_SCND_FORK, philo);
	write_action(EATS, philo);
	set_long(&(philo->last_meal_time), get_time(0, 1), &(philo->philo_mtx));
	philo->eaten_nb++;
	precise_usleep(philo->dinner->time_to_eat);
	if (philo->dinner->nb_meals != -1
		&& philo->eaten_nb == philo->dinner->nb_meals)
		philo->full = 1;
	handle_mutex(philo->first_fork, UNLOCK);
	handle_mutex(philo->second_fork, UNLOCK);
}

void	*actual_dinner(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	printf("Thread n%d created.\n", philo->philo_id);
	while (get_bool(&(philo->dinner->threads_ready),
		&(philo->dinner->dinner_mtx)) == 0)
		;
	printf("Thread ready.\n");
	while (philo->dinner->finished == 0)
	{
		if (philo->full)
			break ;
		eating(philo);
		sleeping(philo);
		write_action(THINKS, philo);
	}
	return (NULL);
}

void	begin_simulation(t_dinner *dinner)
{
	int	i;

	i = 0;
	while (i < dinner->nb_philo)
	{
		handle_thread(&(dinner->philos[i].philo_thread), actual_dinner,
		&(dinner->philos[i]), CREATE);
		i++;
	}
	set_bool(&(dinner->threads_ready), 1, &(dinner->dinner_mtx));
	set_long(&(dinner->start_time), get_time(0, 1), &(dinner->dinner_mtx));
	while (--i >= 0)
		handle_thread(&(dinner->philos[i].philo_thread), NULL, NULL, JOIN);
}
