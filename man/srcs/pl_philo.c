/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pl_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichan <yichan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 16:32:48 by yichan            #+#    #+#             */
/*   Updated: 2023/02/07 23:43:32 by yichan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	pl_check_full(t_thread *pl, t_book *record)
{
	(void)pl;
	if (record->full_counter == record->pl_num)
	{
		pl_call_end(pl);
		return (1);
	}
	return (0);
}

/**
 * @brief the thread waits for the mutex to become available.
 * 			Format: void *(*start_routine)(void *),
 *
 * @param pl
 * @return void*
 */

void	*motherfucker(void *temp)
{
	t_thread	*pl;
	t_book		*record;

	pl = (t_thread *)temp;
	record = pl->record;
	// pthread_mutex_lock(record->printer);
	pl->starttime = pl_time();
	pl->last_meal = pl_time();
	// pthread_mutex_unlock(record->printer);
	if (pl->id % 2 == 0)
		pl_usleep(pl->record->time_to_eat / 2);
	while (1)
	{
		if (pl_eat(pl, record) == 1)
			return (NULL);
		if (pl_sleep_think(pl, record) == 1)
			return (NULL);
	}
	return (NULL);
}

// (void *)&pl[i]) is to passed in the portion memory of a struct.
int	pl_run_trd(t_thread *pl, t_book *record)
{
	pthread_t	*thread;
	pthread_t	*checker;
	int			i;

	thread = (pthread_t *)ft_calloc(sizeof(pthread_t) * record->pl_num);
	checker = (pthread_t *)ft_calloc(sizeof(pthread_t));
	record->starttime = pl_time();
	i = -1;
	while (++i < record->pl_num)
	{
		if (pthread_create(&thread[i], NULL,
				&motherfucker, (void *)&pl[i]) != 0)
			return (err_display("Pthread Create Error"));
	}
	i = -1;
	if (pthread_create(&checker[0], NULL, &pl_checker, (void *)pl) != 0)
		return (err_display("Pthread Create Error"));
	while (++i < record->pl_num)
		pthread_detach(thread[i]);
	pthread_join(*checker, NULL);
	pthread_mutex_destroy(record->printer);
	i = -1;
	while (++i < record->pl_num)
		pthread_mutex_destroy(pl[i].l_fork);
	return (free(thread), free(checker), 0);
}

int	philo(t_book *record)
{
	t_thread		*pl;
	pthread_mutex_t	*fork;

	pl = (t_thread *)ft_calloc(sizeof(t_thread) * (record->pl_num));
	fork = (pthread_mutex_t *)ft_calloc(sizeof(pthread_mutex_t)
			* record->pl_num);
	record->printer = (pthread_mutex_t *)ft_calloc(sizeof(pthread_mutex_t) * 1);
	pthread_mutex_init(record->printer, NULL);
	record->plptr = pl;
	if (pl_init_pl(pl, fork, record->printer, record) != 0)
		return (1);
	if (pl_run_trd(pl, record) != 0)
		return (1);
	return (free(pl), free(fork), free(record->printer), 0);
	// return (0);
}
