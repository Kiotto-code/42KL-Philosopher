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
	// record->printer = action;
	while (++i < record->pl_num)
	{
		// printf("fork:%d\n", pthread_mutex_init(&fork[i], NULL));
		if (pthread_mutex_init(&fork[i], NULL) != 0)
			err_display("fork failed");
		pl[i].fulfilled = 0;
		pl[i].record = record;
		pl[i].record->printer = action;
		pl[i].id = i +1;
		pl[i].l_fork = &fork[i];
		pl[i].r_fork = &fork[(i + 1) % record->pl_num];
		pl[i].last_meal = 0;
		pl[i].num_meals = 0;
	}
	return (0);
}