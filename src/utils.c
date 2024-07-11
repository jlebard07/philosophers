/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:17:12 by jlebard           #+#    #+#             */
/*   Updated: 2024/06/28 16:17:12 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	exit_error(char *s)
{
	printf("%s", s);
	exit(EXIT_FAILURE);
}

long	get_time(bool sc)
{
	struct	timeval	time;
	
	if (gettimeofday(&time, NULL) == -1)
		exit_error("Echec dans la récupération de l'heure.\n");
	if (sc)
		return (time.tv_sec + time.tv_usec / 1e6);
	else
		return (time.tv_usec + time.tv_sec * 1e6);
	error_exit("Mauvais arguments pour get_time.\n");
	return (0);
}

void	my_usleep(long usec, t_dinner *dinner)
{
	long	start_sleep;
	long	rem;

	start_sleep = get_time(0);
	while (get_time(0) - start_sleep < usec)
	{
		if (dinner->rules.finish == 1)
			break;
		rem = usec - (get_time(0) - start_sleep);
		if (rem > 1e3)
			usleep(rem / 2);
		else 
			while (get_time(0) - start_sleep < usec)
				;
	}
}

void	write_status(t_status code, t_philo	*philo)
{
	handle_mutex(&(philo->atable->write_mutex), LOCK);
	if (code == TAKE_FIRST_FORK || code == TAKE_SECOND_FORK)
		printf("time : %ld\nPhilo n %d has taken a fork.\n", get_time(0), philo->id_philo);
	else if (code == EAT)
		printf("time : %ld\nPhilo n %d has eaten.\n", get_time(0), philo->id_philo);
	else if (code == SLEEP)
		printf("time : %ld\nPhilo n %d sleeps.\n", get_time(0), philo->id_philo);
	else if (code == THINK)
		printf("time : %ld\nPhilo n %d thinks.\n", get_time(0), philo->id_philo);
	else if (code == DEAD)
		printf("time : %ld\nPhilo n %d is dead.\n", get_time(0), philo->id_philo);
	handle_mutex(&(philo->atable->write_mutex), UNLOCK);
}
