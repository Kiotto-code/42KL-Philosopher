/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pl_simulate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichan <yichan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 00:29:13 by yichan            #+#    #+#             */
/*   Updated: 2023/05/01 01:53:51 by yichan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	pl_timeinterval(long start_time)
{
	return (pl_time() - start_time);
}

long	pl_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

//set last meal time
void	pl_lmeal_time(t_philo *philo)
{
	sem_wait(philo->lmeal_rec);
	philo->last_meal = pl_time();
	sem_post(philo->lmeal_rec);
}

void	philo_simulation(t_philo *philo)
{
	pthread_t checker;

	pl_lmeal_time(&philo);
	pthread_create(&checker, NULL, &pl_checker, philo);
}