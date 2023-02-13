/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pl_extra_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichan <yichan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 22:16:52 by yichan            #+#    #+#             */
/*   Updated: 2023/02/13 23:46:27 by yichan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pl_call_end(t_thread *pl)
{
	int	i;

	i = -1;
	// printf("checking \n");
	// pthread_mutex_lock(pl->l_fork);
	while (++i < pl->record->pl_num)
	{
		pl[i].end = 1;
	}
	// pthread_mutex_unlock(pl->l_fork);
	// usleep(500);
}

int	meal_target_check(t_thread *pl, int *i)
{
	t_book	*record;

	record = pl->record;
	pthread_mutex_lock(record->printer);
	if (*i >= pl->record->pl_num)
		*i = 0;
	if (pl->record->meal_target > 0)
	{
		if (record->full_counter == record->pl_num)
		{
			pl_call_end(pl);
			pthread_mutex_unlock(record->printer);
			return (1);
		}
	}
	pthread_mutex_unlock(record->printer);
	return (0);
}

int	pl_eat(t_thread *pl, t_book	*record)
{
	pthread_mutex_lock((*pl).l_fork);
	if (pl_show(pl, FORK, record->printer) == 1)
	{
		pthread_mutex_unlock((*pl).l_fork);
		return (1);
	}
	pthread_mutex_lock((*pl).r_fork);
	if (pl_show(pl, FORK, record->printer) == 1)
	{
		pthread_mutex_unlock((*pl).r_fork);
		return (1);
	}
	if (pl_show(pl, EAT, record->printer) == 1)
	{
		pthread_mutex_unlock(pl->l_fork);
		pthread_mutex_unlock(pl->r_fork);
		return (1);
	}
	// pl->last_meal = pl_time();
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
	// if (pl->end == 1)
	// 	return (1);
	return (0);
}

// long int	pl_diff(long a, long b)
// {
// 	return (a - b);
// }
