/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:13:26 by jlebard           #+#    #+#             */
/*   Updated: 2024/06/28 16:13:26 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int		main(int argc, char **argv)
{
	t_dinner	dinner;
	
	if (argc != 5 && argc != 6)
		exit_error("Rentrez le bon nombre d'arguments\n");
	parse(dinner.rules, argv);
	innit_dinner(&dinner);
	time_to_eat(&dinner);
}