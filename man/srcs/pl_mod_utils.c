/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pl_mod_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichan <yichan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 16:44:28 by yichan            #+#    #+#             */
/*   Updated: 2023/02/07 23:37:56 by yichan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*pl_checker(void *temp)
{
	int			i;
	t_thread	*pl;
	long		current;

	i = 0;
	pl = (t_thread *)temp;
	pl_usleep(50);
	current = pl_time();
	while (1)
	{
		if (meal_target_check(pl, &i, &current) == 1)
			return ((void *)1);
		pl->record->temp = pl_time();
		pthread_mutex_lock(pl->record->full_mut);
		if (pl_deadcheck(&pl[i]) == (void *)1)
		{
			pthread_mutex_unlock(pl->record->full_mut);
			return (NULL);
		}
		pthread_mutex_unlock(pl->record->full_mut);
		i++;
	}
	return (NULL);
}

void	pl_usleep(long num)
{
	long	i;
	long	total;

	i = pl_time();
	total = num + i;
	while (1)
	{
		usleep(500);
		if (pl_time() >= total)
			break ;
	}
}

int	pl_eatcheck(t_thread *pl, char *msg)
{
	if (msg[3] == 'e')
	{
		pl->temp = pl_time();
		pthread_mutex_lock(pl->record->full_mut);
		pl->num_meals += 1;
		if (pl->record->meal_target > 0 && \
			pl->num_meals == pl->record->meal_target)
			pl->record->full_counter += 1;
		if (pl_check_full(pl, pl->record) == 1)
		{
			pthread_mutex_unlock(pl->record->full_mut);
			return (1);
		}
		pl->last_meal = pl->temp;
		pthread_mutex_unlock(pl->record->full_mut);
	}
	return (0);
}

// ◦ timestamp_in_ms X has taken a fork
// ◦ timestamp_in_ms X is eating
// ◦ timestamp_in_ms X is sleeping
// ◦ timestamp_in_ms X is thinking
// ◦ timestamp_in_ms X died

int	pl_show(t_thread *pl,
			char *msg, pthread_mutex_t *printer)
{
	unsigned int	timestamp;

	timestamp = pl_time() - pl->starttime;
	pthread_mutex_lock(pl->record->end_mut);
	if (pl->end == 1)
	{
		pthread_mutex_unlock(pl->record->end_mut);
		return (1);
	}
	pthread_mutex_unlock(pl->record->end_mut);
	if (pl_show_run(timestamp, pl, msg, printer) == 1)
		return (1);
	if (pl_eatcheck(pl, msg) == 1)
		return (1);
	return (0);
}

int	pl_show_run(unsigned int timestamp, t_thread *pl,
				char *msg, pthread_mutex_t *printer)
{
	pthread_mutex_lock(printer);
	if (pl->record->printswitch == OFF)
	{
		pthread_mutex_lock(printer);
		return (1);
	}
	if (msg[3] == 'd')
	{
		printf("%u %ld %s\n", timestamp, pl->id, msg);
		pl->record->printswitch = OFF;
		pthread_mutex_unlock(printer);
		return (1);
	}
	else
		printf("%u %ld %s\n", timestamp, pl->id, msg);
	pthread_mutex_unlock(printer);
	return (0);
}
