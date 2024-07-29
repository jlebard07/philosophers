/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:31:55 by jlebard           #+#    #+#             */
/*   Updated: 2024/07/11 16:31:55 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static bool not_too_long(char *s)
{
	int	i;
	i = 0;

	while (s[i])
		i++;
	if (i > 10)
		return (0);
	return (1);
}

static long	ft_atol(char *s)
{
	int		i;
	long	res;

	i = 0;
	res = 0;
	while ((s[i] == ' ') || (s[i] > 8 && s[i] < 14))
		i++;
	if ((s[i] < '0' || s[i] > '9') && s[i] != '+')
		return (-1);
	if (s[i] == '+')
		i++;
	if (not_too_long(s + i) == 0)
		return (-1);
	while (s[i])
	{
		if (s[i] < '0' && s[i] > '9')
			return (-1);
		res = res * 10 + (s[i++] - '0');
	}
	if (res > INT_MAX)
		return (-1);
	return (res);
}

int	parse(t_dinner *dinner, char **argv)
{
	int		i;
	long	res;

	i = 0;
	res = 0;
	dinner->nb_meals = -1;
	while (argv[++i])
	{
		res = ft_atol(argv[i]);
		if (res == -1)
			return (-1);
		if (i == 1)
			dinner->nb_philo = (int)res;
		else if (i == 2)
			dinner->time_to_die = res;
		else if (i == 3)
			dinner->time_to_eat = res;
		else if (i == 4)
			dinner->time_to_sleep = res;
		else if (i == 5)
			dinner->nb_meals = res;
	}
	return (0);
}
