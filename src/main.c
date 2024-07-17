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

int	main(int argc, char **argv)
{
	t_dinner	dinner;
	
	if (argc == 5 || argc == 6)
	{
		if (parse(&dinner, argv) == -1)
		{
			ft_putstr_fd("Please enter correct args.\n", 2);
			return (1);
		}
		if (init_data(&dinner) == -1)
			return (1);
		begin_simulation(&dinner);
	}
	else
		ft_putstr_fd("Please enter 5 or 6 args.\n", 2);
	return (0);
}