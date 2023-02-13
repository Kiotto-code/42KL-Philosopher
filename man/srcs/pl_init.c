/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pl_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichan <yichan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 17:50:56 by yichan            #+#    #+#             */
/*   Updated: 2023/02/07 17:28:08 by yichan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	pl_init_pl(t_thread *pl, pthread_mutex_t *fork,
	pthread_mutex_t *action, t_book *record)
{
	int	i;

	i = -1;
	(void) action;
	while (++i < record->pl_num)
	{
		if (pthread_mutex_init(&fork[i], NULL) != 0)
			err_display("fork failed");
		pl[i].fulfilled = 0;
		pl[i].record = record;
		pl[i].id = i +1;
		pl[i].l_fork = &fork[i];
		pl[i].r_fork = &fork[(i + 1) % record->pl_num];
		pl[i].last_meal = 0;
		pl[i].num_meals = 0;
		pl[i].starttime = 0;
		pl[i].end = 0;
		pl[i].pl_num = record->pl_num;
		pl[i].time_to_die = record->time_to_die;
		pl[i].time_to_eat = record->time_to_eat;
		pl[i].time_to_sleep = record->time_to_sleep;
		pl[i].meal_target = record->meal_target;
	}
	return (0);
}
