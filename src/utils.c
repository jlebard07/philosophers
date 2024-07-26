/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 10:43:18 by jlebard           #+#    #+#             */
/*   Updated: 2024/07/26 17:15:19 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long	get_time(bool second, bool mls)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	if (second == 1)
		return (time.tv_sec + time.tv_usec / 1e6);
	else if (mls == 1)
		return (time.tv_sec * 1e3 + time.tv_usec / 1e3);
	else
		return (time.tv_sec * 1e6 + time.tv_usec);
	return (0);
}

void	precise_usleep(long time_to_sleep)
{
	long	start;
	long	time_left;

	start = get_time(0, 0);
	while (get_time(0, 0) - start < time_to_sleep)
	{
		time_left = (time_to_sleep - (get_time(0, 0) - start));
		if (time_left > 1000)
			usleep(time_left / 2);
		else
			while (get_time(0, 0) - start < time_to_sleep)
				;
	}
}

void	write_action(t_action_code code, t_philo *philo)
{
	long	time_goes_by_so_slowly;
	
	if (philo->dinner->finished == 1)
		return ;
	time_goes_by_so_slowly = get_time(0, 1) - philo->dinner->start_time;
	handle_mutex(&(philo->dinner->write_mtx), LOCK);
	if (code == EATS)
		printf(B"%-5ld"RST"The philo %d is eating.\n",
		time_goes_by_so_slowly, philo->philo_id);		
	else if (code == THINKS)
		printf(B"%-5ld"RST"The philo %d is thinking.\n",
		time_goes_by_so_slowly, philo->philo_id);
	else if (code == SLEEPS)
		printf(B"%-5ld"RST"The philo %d is sleeping.\n",
		time_goes_by_so_slowly, philo->philo_id);
	else if (code == TAKE_FIRST_FORK)
		printf(B"%-5ld"RST"The philo %d has grabbed fork 1.\n",
		time_goes_by_so_slowly, philo->philo_id);	
	else if (code == TAKE_SCND_FORK)
		printf(B"%-5ld"RST"The philo %d has grabbed fork 2.\n",
		time_goes_by_so_slowly, philo->philo_id);		
	else if (code == DEAD)
		printf(B"%-5ld"RST"The philo %d is dead.\n",
		time_goes_by_so_slowly, philo->philo_id);
	handle_mutex(&(philo->dinner->write_mtx), UNLOCK);
}

