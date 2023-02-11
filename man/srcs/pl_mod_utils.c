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

// int	pl_td_crt(pthread_t *restrict thread,
// 		const pthread_attr_t *restrict attr,
// 		void *(*start_routine)(void *),
// 		void *restrict arg)
// {
// 	if (pthread_create (thread, attr, start_routine, arg) != 0)
// 	{
// 		printf("threead create failed");
// 		return (1);
// 	}
// }
void	*pl_checker(void *temp)
{
	int			i;
	t_thread	*pl;

	i = 0;
	pl = (t_thread *)temp;
	pl_usleep(50);
	while (1)
	{
		if (meal_target_check(pl, &i) == 1)
			return ((void *) 1);
		if ((pl_time() - pl[i].last_meal) > pl->record->time_to_die)
		{
			pl->record->end = 1;
			pl_show_run(pl_time() - pl[i].record->starttime, \
						pl[i].id, DIED, pl[i].record->printer);
			return ((void *) 1);
		}
		i++;
		pthread_mutex_unlock(pl->record->printer);
	}
	return (NULL);
}

void	pl_usleep(long num)
{
	long	i;

	i = pl_time();
	while (1)
	{
		usleep(50);
		if ((pl_time() - i) >= num)
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

int	pl_show(unsigned timestamp, t_thread *pl,
	char *msg, pthread_mutex_t *printer)
{
	pthread_mutex_lock(pl->record->printer);
	usleep(100);
	if (pl->record->end == 1)
	{
		pthread_mutex_unlock(printer);
		return (1);
	}
	if (pl_check_full(pl->record->plptr, pl->record) == 1)
	{
		pthread_mutex_unlock(printer);
		return (1);
	}
	pl_show_run(timestamp, pl->id, msg, printer);
	if (msg[3] == 'e')
	{
		pl->num_meals += 1;
		if (pl->record->meal_target > 0 && \
			pl->num_meals == pl->record->meal_target)
			pl->record->full_counter += 1;
		if (pl_check_full(pl->record->plptr, pl->record) == 1)
			return (1);
	}
	pthread_mutex_unlock(printer);
	return (0);
}

void	pl_show_run(unsigned int timestamp, int id,
	char *msg, pthread_mutex_t *printer)
{
	(void)printer;
	if (msg[3] == 'd')
	{
		printf("%u %d %s\n", timestamp, id, msg);
		return ;
	}
	else
		printf("%u %d %s\n", timestamp, id, msg);
}
