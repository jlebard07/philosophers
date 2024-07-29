/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 10:43:01 by jlebard           #+#    #+#             */
/*   Updated: 2024/07/17 10:43:01 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	set_bool(bool *dest, bool b, pthread_mutex_t *mtx)
{
	handle_mutex(mtx, LOCK);
	*dest = b;
	handle_mutex(mtx, UNLOCK);
}

bool	get_bool(bool *to_get, pthread_mutex_t *mtx)
{
	bool	dest;

	dest = 0;
	handle_mutex(mtx, LOCK);
	dest = *to_get;
	handle_mutex(mtx, UNLOCK);
	return (dest);
}

void	set_long(long *dest, long l, pthread_mutex_t *mtx)
{
	handle_mutex(mtx, LOCK);
	*dest = l;
	handle_mutex(mtx, UNLOCK);
}

long	get_long(long *to_get, pthread_mutex_t *mtx)
{
	long	dest;

	dest = 0;
	handle_mutex(mtx, LOCK);
	dest = *to_get;
	handle_mutex(mtx, UNLOCK);
	return (dest);
}

void	inc_long(long *dest, pthread_mutex_t *mtx)
{
	handle_mutex(mtx, LOCK);
	(*dest)++;
	handle_mutex(mtx, UNLOCK);
}
