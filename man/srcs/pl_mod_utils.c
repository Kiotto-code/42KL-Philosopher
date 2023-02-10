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
	int		i;
	t_thread	*pl;

	i = 0;
	pl = (t_thread *)temp;
	while (1)
	{
		pthread_mutex_lock(pl[0].record->printer);
		usleep(100);
		if (i >= pl[0].record->pl_num)
			i = 0;
		if (pl[0].record->meal_target > 0)
		{
			if (pl_check_full(pl, pl->record) == 1)
				return (NULL);
		}
		if ((pl_time() - pl[i].last_meal) > pl[i].record->time_to_die)
		{
			pl[0].record->end = 1;
			pl_show(pl_time() - pl[i].record->starttime, \
						pl, DIED, pl[0].record->printer);
			return ((void *) 1);
		}
		i++;
		pthread_mutex_unlock(pl[0].record->printer);
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

// int	pl_show(unsigned timestamp, t_thread *pl, char *msg, pthread_mutex_t *printer)
// {
// 	// if (pl_check_full(pl, pl->record) == 1)
// 	// 	return (1);
// 	// usleep(50/10000);
// 	// if (pl->record->end == 1)
// 	// {
// 	// 	while (1)
// 	// 		;
// 	// }
// 	if(pl->record->end == 1)
// 		return (1);
// 	pthread_mutex_lock(printer);
// 	pl_show_run((long)timestamp, pl->id, msg, printer);
// 	if (msg[3] == 'e')
// 	{
// 		// pl->num_meals += 1;
// 		// usleep(50);
// 		// if (pl_check_full(pl, record) == 1)
// 		// 	break;
// 		if (pl->num_meals >= pl->record->meal_target && pl->record->meal_target > 0)
// 			pl->fulfilled = 1;
// 		if (pl_check_full(pl->record->plptr, pl->record) == 1)
// 		{
// 				pthread_mutex_unlock(printer);
// 				// usleep(pl->record->time_to_die);
// 				return (1);
// 		}
// 	}
// 	pthread_mutex_unlock(printer);
// 	return (0);
// }
int	pl_show(unsigned timestamp, t_thread *pl, char *msg, pthread_mutex_t *printer)
{
	// if (pl->record->end == 1)
	// 	return ;
	pthread_mutex_lock(printer);
	if (pl_check_full(pl->record->plptr, pl->record) == 1)
	{
		pthread_mutex_unlock(printer);
		return (1);
	}
	// if (pl->record->end == 1)
	// {
	// 	// pthread_mutex_unlock(printer);
	// 	return (1);
	// }
	pl_show_run(timestamp, pl->id, msg, printer);
	if (msg[3] == 'e')
	{
		pl->num_meals += 1;
		if (pl->num_meals == pl->record->meal_target && pl->record->meal_target > 0)
			pl->record->full_counter += 1;
		// usleep(10);
		if (pl_check_full(pl->record->plptr, pl->record) == 1)
		{
			pthread_mutex_unlock(printer);
			return (1);
		}
	}
	pthread_mutex_unlock(printer);
	return (0);
}

void	pl_show_run(unsigned timestamp, int id, char *msg, pthread_mutex_t *printer)
{
	// pthread_mutex_lock(printer);
	(void)printer;
	if (msg[3] == 'd')
	{
		printf("%u %d %s\n", timestamp, id, msg);
		return ;
	}
	else
		printf("%u %d %s\n", timestamp, id, msg);
	// pthread_mutex_unlock(printer);
}
