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
	t_rules	rules;
	
	if (argc != 5 && argc != 6)
		exit_error("Rentrez le bon nombre d'arguments\n");
	parse(&rules, argv);
	
}