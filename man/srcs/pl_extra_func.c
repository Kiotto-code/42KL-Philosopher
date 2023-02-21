/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pl_extra_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichan <yichan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 22:16:52 by yichan            #+#    #+#             */
/*   Updated: 2023/02/21 16:52:56 by yichan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pl_call_end(t_thread *pl)
{
	int	i;

	i = -1;
	pthread_mutex_lock(pl->record->end_mut);
	pl->record->end = 1;
	while (++i < pl->record->pl_num)
	{
		pl[i].end = 1;
	}
	pthread_mutex_unlock(pl->record->end_mut);
}

int	meal_target_check(t_thread *pl, int *i, long *current)
{
	t_book	*record;

	record = pl->record;
	if (*i >= pl->record->pl_num)
	{
		*i = 0;
		*current = pl_time();
		usleep(pl->time_to_eat * pl->pl_num);
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
	pl->temp = pl_time() - pl->starttime;
	if (pthread_mutex_lock((*pl).l_fork) == 1)
		return (pthread_mutex_unlock((*pl).l_fork), 1);
	pl_show(pl, FORK, record->printer);
	if (pthread_mutex_lock((*pl).r_fork) == 1)
		return (pthread_mutex_unlock((*pl).l_fork),
			pthread_mutex_unlock((*pl).r_fork), 1);
	pl_show(pl, FORK, record->printer);
	if (pl_show(pl, EAT, record->printer) == 1)
	{
		pthread_mutex_unlock(pl->l_fork);
		pthread_mutex_unlock(pl->r_fork);
		return (1);
	}
	pl_usleep(record->time_to_eat);
	pthread_mutex_unlock(pl->l_fork);
	pthread_mutex_unlock(pl->r_fork);
	return (0);
}

int	pl_sleep_think(t_thread *pl, t_book	*record)
{
	if (pl_show(pl, SLEEP, record->printer) == 1)
		return (1);
	pl_usleep(record->time_to_sleep);
	if (pl_show(pl, THINK, record->printer) == 1)
		return (1);
	return (0);
}
