/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 12:15:44 by jlebard           #+#    #+#             */
/*   Updated: 2024/08/01 14:47:15 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	end_simulation(t_dinner *dinner)
{
	if (get_bool(&dinner->finished, &dinner->dinner_mtx) == 1)
		return (1);
	return (0);
}

bool	threads_ready(t_dinner *dinner)
{
	if (get_long(&dinner->ready_nb, &dinner->dinner_mtx) == dinner->nb_philo)
		return (1);
	return (0);
}

static bool	is_dead(t_philo *philo)
{
	long	since_last_meal;

	if (get_bool(&philo->full, &philo->philo_mtx) == 1)
		return (0);
	since_last_meal = get_time(0, 1) - get_long(&philo->last_meal_time,
			&philo->philo_mtx);
	if (since_last_meal > philo->dinner->time_to_die)
		return (1);
	return (0);
}

void	*f_monitor(void	*data)
{
	t_dinner	*dinner;
	int			i;

	dinner = (t_dinner *)data;
	while (!threads_ready(dinner))
		;
	while (!end_simulation(dinner))
	{
		i = -1;
		while (++i < dinner->nb_philo && !end_simulation(dinner))
		{
			if (is_dead(dinner->philos + i))
			{
				write_action(DEAD, &dinner->philos[i]);
				set_bool(&dinner->finished, 1, &dinner->dinner_mtx);
			}
		}
	}
	return (NULL);
}	
