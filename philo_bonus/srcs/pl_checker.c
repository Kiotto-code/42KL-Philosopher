/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pl_checker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichan <yichan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 01:47:16 by yichan            #+#    #+#             */
/*   Updated: 2023/07/13 10:44:56 by yichan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// static void	piter_badend(unsigned int i, t_data *record)
// {
// 	if (kill(record->num_pid[i], SIGINT) != -1)
// 		waitpid(record->num_pid[i], NULL, 0);
// }

void	philo_sim_status(t_data *record)
{
	int	i;

	waitpid(-1, NULL, 0);
	i = -1;
	while (++i < record->num_phls)
	{
		if (kill(record->num_pid[i], SIGINT) != -1)
			waitpid(record->num_pid[i], NULL, 0);
	}
}

long	lmeal_interv(t_philo *philo)
{
	long	interval;

	// semaphore_report(sem_wait, philo->lmeal_rec);
	// interval = time_get(&philo->time_lastmeal) - philo->last_meal;
	// interval = pl_time() - philo->check_meal;
	interval = pl_time() - (philo->time_lastmeal.s_time.tv_sec *1000
		+ philo->time_lastmeal.s_time.tv_sec /1000);
	// semaphore_report(sem_post, philo->lmeal_rec);
	return (interval);
}

void	*pl_checker(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (lmeal_interv(philo) < philo->data->tm_die)
		usleep(500 / 2);
	philo_log(philo, DEAD);
	exit(1);
	return (NULL);
}
