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
	t_book		*record;

	i = 0;
	pl = (t_thread *)temp;
	record = pl->record;
	pl_usleep(50);
	while (1)
	{
		if (meal_target_check(pl, &i) == 1)
			return ((void *) 1);
		pthread_mutex_lock(pl->record->full_mut);
		if ((pl_time() - pl[i].last_meal) > pl->time_to_die)
		{
			// pthread_mutex_unlock(pl[i].record->printer);
			// pthread_mutex_lock(pl->record->printer);
			pl_call_end(pl);
			// pthread_mutex_unlock(pl->record->printer);
			pl_show_run(pl_time() - pl[i].starttime, \
						pl[i].id, DIED, pl[i].record->printer);
			pthread_mutex_unlock(pl->record->full_mut);
			return ((void *) 1);
		}
		pthread_mutex_unlock(pl->record->full_mut);
		// pthread_mutex_unlock(pl->record->printer);
		i ++;
		usleep(100);
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
		usleep(50);
		if (pl_time() >= total)
			break ;
	}
}

long	pl_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
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

	// printf("pl->record->end_mut %p \n", pl->record->end_mut);
	pthread_mutex_lock(pl->record->end_mut);
	if (pl->end == 1)
	{
		pthread_mutex_unlock(pl->record->end_mut);
		return (1);
	}
	timestamp = pl_time() - pl->starttime;
	pthread_mutex_unlock(pl->record->end_mut);
	pl_show_run(timestamp, pl->id, msg, printer);
	if (msg[3] == 'e')
	{
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
		pl->last_meal = pl_time();
		pthread_mutex_unlock(pl->record->full_mut);
	}
	return (0);
}

void	pl_show_run(unsigned int timestamp, int id,
	char *msg, pthread_mutex_t *printer)
{
	pthread_mutex_lock(printer);
	(void)printer;
	if (msg[3] == 'd')
	{
		printf("%u %d %s\n", timestamp, id, msg);
	}
	else
		printf("%u %d %s\n", timestamp, id, msg);
	pthread_mutex_unlock(printer);
}
