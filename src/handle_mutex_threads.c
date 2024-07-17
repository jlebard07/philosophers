/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mutex_threads.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 17:07:17 by jlebard           #+#    #+#             */
/*   Updated: 2024/07/11 17:07:17 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	handle_mutex_bis(pthread_mutex_t *mtx, t_mutex_code code)
{
	if (code == INIT)
		pthread_mutex_init(mtx, NULL);
	else if (code == DESTROY)
	{
		if (pthread_mutex_destroy(mtx) != 0)
			return (-1);
	}
	else if (code == LOCK)
	{
		if (pthread_mutex_lock(mtx) != 0)
			return (-1);
	}
	else if (code == UNLOCK)
	{
		if (pthread_mutex_lock(mtx) != 0)
			return (-1);
	}
	return (0);
}

int	handle_mutex(pthread_mutex_t *mtx, t_mutex_code code)
{
	if (handle_mutex_bis(mtx, code) == -1)
	{
		if (code == DESTROY)
			printf(R "An error occured destroying a mutex.\n" RST);
		else if (code == LOCK)
			printf(R "An error occured locking a mutex.\n" RST);
		else if (code == UNLOCK)
			printf(R "An error occured unlocking a mutex.\n" RST);
		return (-1);
	}
	return (0);
}

static int	handle_thread_bis(pthread_t *th, void *(*f)(void *), void *data,
					t_thread_code code)
{
	if (code == CREATE)
	{
		if (pthread_create(th, NULL, f, data) != 0)
			return (-1);
	}
	else if (code == JOIN)
	{
		if (pthread_join(*th, NULL) != 0)
			return (-1);
	}
	else if (code == DETACH)
	{
		if (pthread_detach(*th) != 0)
			return (-1);
	}
	return (0);
}

int	handle_thread(pthread_t *th, void *(*f)(void *), void *data,
					t_thread_code code)
{
	if (handle_thread_bis(th, f, data, code) == -1)
	{
		if (code == CREATE)
			printf(R "An error occured creating a thread.\n" RST);
		else if (code == JOIN)
			printf(R "An error occured joining a thread.\n" RST);
		else if (code == DETACH)
			printf(R "An error occured detaching a thread.\n" RST);
		return (-1);
	}
	return (0);
}