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

void	*start_threads(t_dinner *dinner)
{
	while 
}

int	begin_simulation(t_dinner *dinner)
{
	int	i;

	i = 0;
	while (i < dinner->nb_philo)
		if (handle_thread(&(dinner->philos[i].philo_thread), start_threads,
			dinner, CREATE) == -1)
		return (-1);
	dinner->threads_ready = 1;
}
