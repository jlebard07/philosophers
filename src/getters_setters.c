/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 17:38:19 by jlebard           #+#    #+#             */
/*   Updated: 2024/07/05 17:38:19 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	set_bool(pthread_mutex_t mtx, bool *dest, bool value)
{
	handle_mutex(&mtx, LOCK);
	*dest = value;
	handle_mutex(&mtx, UNLOCK);
}

bool	get_bool(pthread_mutex_t mtx, bool *value)
{
	bool	dest;
	handle_mutex(&mtx, LOCK);
	dest = *value;
	handle_mutex(&mtx, UNLOCK);
	return (dest);
}

void	set_long(pthread_mutex_t mtx, long *dest, long value)
{
	handle_mutex(&mtx, LOCK);
	*dest = value;
	handle_mutex(&mtx, UNLOCK);
}

long	get_long(pthread_mutex_t mtx, long *value)
{
	bool	dest;
	handle_mutex(&mtx, LOCK);
	dest = *value;
	handle_mutex(&mtx, UNLOCK);
	return (dest);
}
