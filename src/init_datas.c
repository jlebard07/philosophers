/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_datas.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 19:39:05 by jlebard           #+#    #+#             */
/*   Updated: 2024/06/30 19:39:05 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	init_rules(t_rules	*rules)
{
	int	i;

	i = 0;
	t_rules->forks = malloc(sizeof(t_fork) * t_rules->nb_of_philo);
	if (t_rules->forks = NULL)
		exit_error("Pb Malloc\n");
	while (t_rules->forks[i])
	{
		if (pthread_mutex_init(&(t_fork->forks[i++].fork), NULL) != 0)
			exit_error("Erreur lors de l'initialisation d'un mutex");
	}
}
