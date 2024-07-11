/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_dinner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:57:30 by jlebard           #+#    #+#             */
/*   Updated: 2024/07/04 18:57:30 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	wait_all_threads(t_philo *philo)
{
	while (!(philo->atable->threads_ready))
		return ;
}

void	*start_simulation(t_philo *philo)
{
	wait_all_threads(philo);
}

void	time_to_eat(t_dinner *dinner)
{
	int	i;

	i = 0;
	if (dinner->rules.nb_of_philo == 0 || dinner->rules.nb_of_philo == 1)
	{
		free_dinner(dinner);
		exit_error("Il doit y avoir au minimum 2 philosophes \
		pour commencer la simulation");
	}
	while (i < dinner->rules.nb_of_philo)
		handle_thread(&(dinner->philos[i].th_philo), start_simulation, &(dinner->philos[i++]), CREATE);
	set_bool(dinner->rules.rules_mtx, &(dinner->rules.threads_ready), true);
}
