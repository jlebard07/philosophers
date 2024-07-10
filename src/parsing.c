/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:22:56 by jlebard           #+#    #+#             */
/*   Updated: 2024/06/28 16:22:56 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static bool	iss_space(char c)
{
	return ((c > 8 && c < 14) || c == 32);
}

static bool	is_valid(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || (str[i] < 48 && str[i] > 57))
		return (0);
	while (str[i] > 48 && str[i] < 57)
		i++;
	if (i > 10)
		return (0);
	return (1);
}

static long	ft_atol(char *str)
{
	int		i;
	long	res;

	i = 0;
	res = 0;
	while (iss_space(str[i]) == 1)
		i++;
	if (str[i] == '+')
		i++;
	if (is_valid(str + i) == 0)
		exit_error("Veuillez rentrer des arguments valides\n");
	while (str[i] > 48 && str[i] < 57)
		res = res * 10 + (str[i++] - 48);
	if (res > INT_MAX)
		exit_error("Veuillez rentrer des arguments valides\n");
	return (res);
}

void	parse(t_rules rules, char **argv)
{
	rules.nb_of_philo = (int)ft_atol(argv[1]);
	rules.die_time = ft_atol(argv[2]);
	rules.eat_time = ft_atol(argv[3]);
	rules.sleep_time = ft_atol(argv[4]);
	if (argv[5])
		rules.must_eat = ft_atol(argv[5]);
}
