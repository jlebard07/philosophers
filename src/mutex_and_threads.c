/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_and_threads.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:03:33 by jlebard           #+#    #+#             */
/*   Updated: 2024/07/02 17:03:33 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	mutex_error(int status, t_mtxcode mtxcode)
{
	if (status == 0)
		return 
	else if (status == EINVAL && (mtxcode == LOCK || mtxcode == UNLOCK))
		exit_error("The value specified by mutex is unintialized.\n");
	else if (status == EINVAL && (mtxcode == CREATE))
		exit_error("The value specified by atr is invalid.\n")
	else if (status == EDEADLK)
		exit_error("Mutex is locked by another thread.\n")
	else if (status == ENOMEM)
		exit_error("Not enough memory to create another mutex.\n")
	else
		exit_error("An error outside code's specification happened with \
		mutex.\n");
}

static void	thread_error(int status, t_thcode thcode)
{
	if (status == 0)
		return ;
	else if (status == EAGAIN)
		exit_error("Trop de threads actifs.\n");
	else if (status == EINVAL)
		exit_error("Pas de thread valide spécifié.\n");
	else if (status == EDEADLK)
		exit_error("Appel circulaire entre thread / Appel à soi-même.\n");
	else if (status == ESRCH)
		exit_error("Aucun thread ne correspond à celui entré en arg.\n");
	else if (status == EINVAL)
		exit_error("Thread déjà détaché.\n");
	else
		exit_error("An error outside code's specification happened with \
		threads.\n");
}	

void	handle_mutex(pthread_mutex_t *mutex, t_mtxcode mtxcode)
{
	if (mtxcode == CREATE)
		mutex_error(mtxcode, pthread_mutex_init(mutex, NULL));
	else if (mtxcode == DESTROY)
		mutex_error(mtxcode, pthread_mutex_destroy(mutex));
	else if (mtxcode == LOCK)
		mutex_error(mtxcode, pthread_mutex_lock(mutex));
	else if (mtxcode == UNLOCK)
		mutex_error(mtxcode, pthread_mutex_unlock(mutex));
	else
		exit_error("Wrong code to deal mutex with.\n");
}

void	handle_thread(pthread_t *thread, void *(*f)(void*), void *arg,
						t_thcode thcode)
{
	if (thcode == CREATE)
		thread_error(thcode, pthread_create(thread, NULL, f, arg));
	else if (thcode == JOIN)
		thread_error(thcode, pthread_join(thread, NULL));
	else if (thcode == DETACH)
		thread_error(thcode, pthread_detach(thread));
	else
		exit_error("Wrong code to deal mutex with.\n");
}
