/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pl_extra_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichan <yichan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 22:16:52 by yichan            #+#    #+#             */
/*   Updated: 2023/02/11 22:31:56 by yichan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	meal_target_check(t_thread *pl, int i)
{
	pthread_mutex_lock(pl->record->printer);
	if (i >= pl->record->pl_num)
		i = 0;
	if (pl->record->meal_target > 0)
	{
		if (pl_check_full(pl, pl->record) == 1)
		{
			printf("checking \n");
			pl->record->end = 1;
			return (1);
		}
	}
	return (0);
}

int	pl_eat(t_thread *pl, t_book	*record)
{
	pthread_mutex_lock((*pl).l_fork);
	if (pl_show(pl_time() - record->starttime, pl, FORK, record->printer) == 1)
	{
		pthread_mutex_unlock((*pl).r_fork);
		return (1);
	}
	pthread_mutex_lock((*pl).r_fork);
	if (pl_show(pl_time() - record->starttime, pl, FORK, record->printer) == 1)
	{
		pthread_mutex_unlock((*pl).r_fork);
		return (1);
	}
	if (pl_show(pl_time() - record->starttime, pl, EAT, record->printer) == 1)
		return (1);
	pl->last_meal = pl_time();
	pl_usleep(record->time_to_eat);
	pthread_mutex_unlock(pl->l_fork);
	pthread_mutex_unlock(pl->r_fork);
	return (0);
}

int	pl_sleep_think(t_thread *pl, t_book	*record)
{
	if (pl_show(pl_time() - record->starttime, pl, SLEEP, record->printer) == 1)
		return (1);
	pl_usleep(record->time_to_sleep);
	if (pl_show(pl_time() - record->starttime, pl, THINK, record->printer) == 1)
		return (1);
	if (record->end == 1)
		return (1);
	return (0);
}
