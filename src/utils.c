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

static void	philo_free(t_philo *philos)
{
	int	i;

	i = 0;
	while (philos[i])
	{
		free(philo[i]->first_fork);
		free(philo[i]->second_fork);
		free(philo[i++]);
	}
}

void	free_dinner(t_dinner *dinner)
{
	int	i;*

	i = 0;
	if (dinner->forks)
	{
		while (dinner->forks[i])
		{
			handle_mutex(dinner->forks[i]->mtx_fork, DESTROY);
			free(forks[i++]);
		}
	}
	if (dinner->philo)
		philo_free(dinner->philo);
	free(dinner);
	return ;
}
