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
		record->end = 1;
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
	pl->last_meal = pl_time();
	if (pl->id % 2 == 0)
		usleep(500);
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
	pthread_t	checker;
	int			i;

	thread = (pthread_t *)ft_calloc(sizeof(pthread_t) * record->pl_num);
	record->starttime = pl_time();
	i = -1;
	while (++i < record->pl_num)
	{
		if (pthread_create(&thread[i], NULL,
				&motherfucker, (void *)&pl[i]) != 0)
			return (err_display("Pthread Create Error"));
	}
	i = -1;
	while (++i < record->pl_num)
		pthread_detach(thread[i]);
	if (pthread_create(&checker, NULL, pl_checker, (void *)pl) != 0)
		return (err_display("Pthread Create Error"));
	pthread_join(checker, NULL);
	pthread_mutex_destroy(record->printer);
	i = -1;
	while (++i < record->pl_num)
		pthread_mutex_destroy(pl[i].l_fork);
	return (free(thread), 0);
}

int	philo(t_book *record)
{
	t_thread		*pl;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*act;

	pl = (t_thread *)ft_calloc(sizeof(t_thread) * (record->pl_num));
	fork = (pthread_mutex_t *)ft_calloc(sizeof(pthread_mutex_t)
			* record->pl_num);
	act = (pthread_mutex_t *)ft_calloc(sizeof(pthread_mutex_t) * 1);
	record->plptr = pl;
	record->printer = act;
	if (pl_init_pl(pl, fork, act, record) != 0)
		return (1);
	if (pl_run_trd(pl, record) != 0)
		return (1);
	return (free(pl), free(fork), free(act), 0);
}
