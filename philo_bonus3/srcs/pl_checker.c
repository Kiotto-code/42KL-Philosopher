/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pl_checker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichan <yichan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 01:47:16 by yichan            #+#    #+#             */
/*   Updated: 2023/06/04 23:19:20 by yichan           ###   ########.fr       */
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
	int  i;

	waitpid(-1, NULL, 0);
	i = -1;
	// philo_iter(piter_badend, record);
	while (++i < record->num_phls)
	{
		if (kill(record->num_pid[i], SIGINT) != -1)
			waitpid(record->num_pid[i], NULL, 0);
	}
}

long	lmeal_interv(t_philo *philo)
{
	long	interval;

	semaphore_report(sem_wait, philo->lmeal_rec);
	interval = pl_time() - philo->last_meal;
	semaphore_report(sem_post, philo->lmeal_rec);
	return (interval);
}


void	*pl_checker(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	// printf("%d\n",philo->data->tm_die);
	// printf("%ld\n",philo->last_meal);
	// printf("%p\n",philo->data);
	// semaphore_report(sem_wait, philo->lmeal_rec);
	// printf("last_meaL: %ld\n",pl_time() - philo->last_meal);
	// printf("%d\n",philo->data->tm_die);
	while (lmeal_interv(philo) < philo->data->tm_die)
		usleep(500 / 2);
	// semaphore_report(sem_post, philo->lmeal_rec);
	philo_log(philo, DEAD);
	exit(1);
	return (NULL);
}