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
		return (time.tv_usec + time.tv_usec * 1e6);
	error_exit("Mauvais arguments pour get_time.\n");
	return (0);
}

static void	philo_free(t_philo *philos, int n)
{
	int	i;

	i = 0;
	while (i < n)
		free(&(philos[i++]));
}

// void	free_dinner(t_dinner *dinner)
// {
// 	int	i;

// 	i = 0;
// 	if (dinner->forks)
// 	{
// 		while (i < dinner->rules.nb_of_philo)
// 		{
// 			handle_mutex(dinner->forks[i].mtx_fork, DESTROY);
// 			free(&(dinner->forks[i++]));
// 		}
// 	}
// 	if (dinner->philos)
// 		philo_free(dinner->philos, dinner->rules.nb_of_philo);
// 	free(dinner);
// 	return ;
// }
