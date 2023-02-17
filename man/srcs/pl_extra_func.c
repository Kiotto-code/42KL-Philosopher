/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pl_extra_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichan <yichan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 22:16:52 by yichan            #+#    #+#             */
/*   Updated: 2023/02/17 16:56:51 by yichan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pl_call_end(t_thread *pl)
{
	int	i;

	i = -1;
	// printf("checking \n");
	// printf("pl->record->end_mut %p \n", pl->record->end_mut);
	// printf("pl->record->end_mut %lu \n", sizeof(pl->record->end_mut));
	pthread_mutex_lock(pl->record->end_mut);
	pl->record->end = 1;
	while (++i < pl->record->pl_num)
	{
		// pthread_mutex_lock(pl->record->end_mut);
		pl[i].end = 1;
		// pthread_mutex_unlock(pl->record->end_mut);
	}
	pthread_mutex_unlock(pl->record->end_mut);
	// usleep(500);
}

int	meal_target_check(t_thread *pl, int *i, long current)
{
	t_book	*record;

	record = pl->record;
	if (*i >= pl->record->pl_num)
	{
		*i = 0;
		current = pl_time();
	}
	pthread_mutex_lock(record->full_mut);
	if (pl->record->meal_target > 0)
	{
		if (record->full_counter == record->pl_num)
		{
			pl_call_end(pl);
			pthread_mutex_unlock(record->full_mut);
			return (1);
		}
	}
	pthread_mutex_unlock(record->full_mut);
	return (0);
}

int	pl_eat(t_thread *pl, t_book	*record)
{
	// pthread_mutex_lock((*pl).l_fork);
	// if (pl_show(pl, FORK, record->printer) == 1)
	// {
	// 	pthread_mutex_unlock((*pl).l_fork);
	// 	return (1);
	// }
	// pthread_mutex_lock((*pl).r_fork);
	// if (pl_show(pl, FORK, record->printer) == 1)
	// {
	// 	pthread_mutex_unlock((*pl).l_fork);
	// 	pthread_mutex_unlock((*pl).r_fork);
	// 	return (1);
	// }
	if (pl->id == pl-> pl_num)
	{
		pl->temp = pl_time() - pl->starttime;
		pthread_mutex_lock((*pl).l_fork);
		pl_show(pl, FORK, record->printer);
		// pthread_mutex_unlock((*pl).l_fork);
		pthread_mutex_lock((*pl).r_fork);
		pl_show(pl, FORK, record->printer);
	}
	else
	{
		pl->temp = pl_time() - pl->starttime;
		pthread_mutex_lock((*pl).l_fork);
		pl_show(pl, FORK, record->printer);
		// pthread_mutex_unlock((*pl).l_fork);
		pthread_mutex_lock((*pl).r_fork);
		pl_show(pl, FORK, record->printer);
	}
	// pthread_mutex_unlock((*pl).r_fork);
	if (pl_show(pl, EAT, record->printer) == 1)
	{
		pthread_mutex_unlock(pl->l_fork);
		pthread_mutex_unlock(pl->r_fork);
		return (1);
	}
	pl_usleep(record->time_to_eat);
	pthread_mutex_unlock(pl->l_fork);
	pthread_mutex_unlock(pl->r_fork);
	if (pl->id % 2 == 0)
		usleep(500);
	return (0);
}

int	pl_sleep_think(t_thread *pl, t_book	*record)
{
	if (pl_show(pl, SLEEP, record->printer) == 1)
		return (1);
	pl_usleep(record->time_to_sleep);
	// pthread_mutex_lock(	record->wake_mut)
	// if (pl->id % 2 == 0)
	// {
		
	// }
	// pthread_mutex_lock(record->wake_mut);
	// record->awake += 1;
	// pthread_mutex_unlock(record->wake_mut);
	// while (1)
	// {
	// 	pthread_mutex_lock(record->wake_mut);
	// 	if (record->awake == record->pl_num)
	// 		break ;
	// 	pthread_mutex_unlock(record->wake_mut);
	// }
	// pthread_mutex_unlock(record->wake_mut);
	if (pl_show(pl, THINK, record->printer) == 1)
		return (1);
	if (pl->id % 2 == 0)
		usleep(500);
	// if (pl->end == 1)
	// 	return (1);
	return (0);
}

// long int	pl_diff(long a, long b)
// {
// 	return (a - b);
// }
