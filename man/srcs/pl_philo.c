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

// int pl_check_dead(t_thread *pl, t_book *record)
// {
// 	int i;

// 	i = -1;
// 	while (++i < record->pl_num)
// 	{
// 		if ((pl_time() - pl[i].last_meal) > record->time_to_die)
// 		{
// 			// record->end = 1;
// 			// pthread_mutex_lock(record->printer);
// 			// printf("printre state : %d",pthread_mutex_lock(record->printer));
// 			printf("%d %d %s\n", (int)(pl_time() - record->starttime), pl->id, DIED);
// 			// pl_show(pl_time() - record->starttime,
// 			// 	pl->id, DIED, record->printer);
// 			record->end = 1;
// 			// usleep(50);
// 			return (1);
// 		}
// 	}
// 	return (0);
// }

int pl_check_full(t_thread *pl, t_book *record)
{
	(void)pl;
	// int i;

	// i = -1;
	// while (++i < record->pl_num)
	// {
	// 	if (pl[i].fulfilled == 0)
	// 	{
	// 		// pl_show(pl_time() - record->starttime,
	// 		// 	pl->id, DIED, record->printer);
	// 		return (0);
	// 	}
	// }
	// record->end = 1;

	if (record->full_counter == record->pl_num)
	{
		record->end = 1;
		return (1);
	}

	// usleep(50);
	// pthread_mutex_lock(record->printer);
	return (0);
}

/**
 * @brief the thread waits for the mutex to become available.
 * 			Format: void *(*start_routine)(void *),
 *
 * @param pl
 * @return void*
 */

void *motherfucker(void *temp)
{
	t_thread *pl;
	t_book *record;

	pl = (t_thread *)temp;
	record = pl->record;
	pl->last_meal = pl_time();
	// printf("id: %ld\n", pl->id);
	if (pl->id % 2 == 0)
		usleep(500);
	while (1)
	{
		// printf ("ptr of l_fork %p \n", (*pl).l_fork);
		// printf ("ptr of r_fork %p \n", (*pl).r_fork);
		// printf ("size of l_fork %lu \n", sizeof((*pl).l_fork));
		// printf ("size of r_fork %lu \n", sizeof((*pl).r_fork));
		pthread_mutex_lock((*pl).l_fork);
		if (pl_show(pl_time() - record->starttime, pl, FORK, record->printer) == 1)
		{
			pthread_mutex_unlock((*pl).r_fork);
			return (NULL);
		}
		pthread_mutex_lock((*pl).r_fork);
		if (pl_show(pl_time() - record->starttime, pl, FORK, record->printer) == 1)
		{
			pthread_mutex_unlock((*pl).r_fork);
			return (NULL);
		}
		if (pl_show(pl_time() - record->starttime, pl, EAT, record->printer) == 1)
			return (NULL);
		pl->last_meal = pl_time();
		// printf("last_meal %ld \n", pl->last_meal);
		pl_usleep(record->time_to_eat);
		pthread_mutex_unlock(pl->l_fork);
		pthread_mutex_unlock(pl->r_fork);
		if (pl_show(pl_time() - record->starttime, pl, SLEEP, record->printer) == 1)
			return (NULL);
		pl_usleep(record->time_to_sleep);
		if (pl_show(pl_time() - record->starttime, pl, THINK, record->printer) == 1)
			return (NULL);
		if (record->end == 1)
			return (NULL);
	}
	return (NULL);
}

// (void *)&pl[i]) is to passed in the indexed address of a struct.
int pl_run_trd(t_thread *pl, t_book *record)
{
	pthread_t *thread;
	pthread_t checker;
	int i;

	thread = (pthread_t *)ft_calloc(sizeof(pthread_t) * record->pl_num);
	record->starttime = pl_time();
	i = -1;
	while (++i < record->pl_num)
	{
		if (pthread_create(&thread[i], NULL, &motherfucker, (void *)&pl[i]) != 0)
			return (err_display("Pthread Create Error"));
	}
	i = -1;
	while (++i < record->pl_num)
		pthread_detach(thread[i]);
	if (pthread_create(&checker, NULL, pl_checker, (void *)pl) != 0)
		return (err_display("Pthread Create Error"));
	if (pthread_join(checker, NULL) != 0)
		return (err_display("Pthread Create Error"));
	// while (++i < record->pl_num)
	// 	pthread_join(thread[i], NULL);
	// i= -1;
	// usleep(100);
	pthread_mutex_destroy(record->printer);
	i = -1;
	while (++i < record->pl_num)
		pthread_mutex_destroy(pl[i].l_fork);
	return (free(thread), 0);
}

int philo(t_book *record)
{
	t_thread *pl;
	pthread_mutex_t *fork;
	pthread_mutex_t *act;

	pl = (t_thread *)ft_calloc(sizeof(t_thread) * (record->pl_num));
	fork = (pthread_mutex_t *)ft_calloc(sizeof(pthread_mutex_t) * record->pl_num);
	act = (pthread_mutex_t *)ft_calloc(sizeof(pthread_mutex_t) * 1);
	record->plptr = pl;
	// printf("act:%d\n", pthread_mutex_init(act, NULL));
	// if (pthread_mutex_init(act, NULL) != 0)
	// 	err_display("printer failed ft_calloc");
	// printf("ph number: %d\n", record->pl_num);
	record->printer = act;
	if (pl_init_pl(pl, fork, act, record) != 0)
		return (1);
	if (pl_run_trd(pl, record) != 0)
		return (1);
	// pthread_detach(act[0]);
	// free(pl);
	// free(fork);
	// free(act);
	// usleep(1000 * 1000);
	return (free(pl), free(fork), free(act), 0);
}