/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:29:44 by jlebard           #+#    #+#             */
/*   Updated: 2024/07/11 16:29:44 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	clear_the_table(t_dinner *dinner)
{
	int	i;

	i = 0;
	while (i < dinner->nb_philo)
	{
		handle_mutex(&dinner->philos[i].philo_mtx, DESTROY);
		i++;
	}
	i = 0;
	while (i < dinner->nb_philo)
	{
		handle_mutex(&dinner->forks[i].fork_mtx, DESTROY);
		i++;
	}
	handle_mutex(&dinner->write_mtx, DESTROY);
	handle_mutex(&dinner->dinner_mtx, DESTROY);
	free(dinner->philos);
	free(dinner->forks);
}

int	main(int argc, char **argv)
{
	t_dinner	dinner;
	
	if (argc == 5 || argc == 6)
	{
		if (parse(&dinner, argv) == -1)
		{
			printf(R "Please enter correct args.\n" RST);
			return (1);
		}
		if (init_data(&dinner) == -1)
		{
			clear_the_table(&dinner);
			return (1);
		}
		begin_simulation(&dinner);
		clear_the_table(&dinner);
	}
	else
		printf(R "Please enter 5 or 6 args.\n" RST);
	return (0);
}
