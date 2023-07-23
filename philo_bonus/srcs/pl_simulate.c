/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pl_simulate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichan <yichan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 00:29:13 by yichan            #+#    #+#             */
/*   Updated: 2023/07/24 04:03:29 by yichan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

//time_get
// long	pl_timeinterval(long current_time, long start_time)
// {
// 	return (current_time - start_time);
// }

// long	pl_time(void)
// {
// 	struct timeval	time;

// 	gettimeofday(&time, NULL);
// 	return (time.tv_sec * 1000 + time.tv_usec / 1000);
// }

// //set last meal time
// void	pl_lmeal_time(t_philo *philo)
// {
// 	// sem_wait(philo->lmeal_rec);
// 	semaphore_report(sem_wait, philo->lmeal_rec);
// 	philo->last_meal = pl_time();
// 	// sem_post(philo->lmeal_rec);
// 	semaphore_report(sem_post, philo->lmeal_rec);
// }
static void	philo_eat(t_philo *philo)
{
	semaphore_report(sem_wait, philo->data->fork);
	philo_log(philo, GETFORK);
	semaphore_report(sem_wait, philo->data->fork);
	philo_log(philo, GETFORK);
	pl_lmeal_time(philo);
	philo_log(philo, EAT);
	philo_do(philo, philo->data->tm_eat);
	if (philo->data->mealtarget != -1)
		philo->num_meals++;
	semaphore_report(sem_post, philo->data->fork);
	semaphore_report(sem_post, philo->data->fork);
}

void	philo_simulation(t_philo *philo)
{
	pthread_t	checker;
	// char		*sem_name;

	pl_lmeal_time(philo);
	// sem_name = pl_semname("lmeal_rec", philo->id);
	// philo->lmeal_rec = create_sem(sem_name, O_CREAT | O_EXCL, 0660, 01);
	// free(sem_name);
	pthread_create(&checker, NULL, pl_checker, philo);
	pthread_detach(checker);
	while (1)
	{
		philo_eat(philo);
		philo_log(philo, SLEEP);
		if (philo->data->mealtarget != -1 &&
			philo->num_meals >= philo->data->mealtarget)
		{
			break ;
		}
		philo_do(philo, philo->data->tm_sleep);
		philo_log(philo, THINK);
	}
	semaphore_report(sem_post, philo->data->sem_end);
	exit(0);
}
