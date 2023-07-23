/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pl_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichan <yichan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 22:52:24 by yichan            #+#    #+#             */
/*   Updated: 2023/07/24 05:23:31 by yichan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// void	semaphore_report(sem_t sem_func(sem_t *), sem_t *sem)
// {
// 	const char	*ftname;
// 	int			value;

// 	value = ft(sem);
// 	if (value == 0)
// 		return ;
// 	else if (ft == sem_wait)
// 		ftname = "sem_wait";
// 	else if (ft == sem_post)
// 		ftname = "sem_post";
// 	else if (ft == sem_close)
// 		ftname = "sem_close";
// 	else
// 		ftname = "undefined_function";
// 	printf("semaphore_report: %s(%p) returned: %d\n", ftname, sem, value);
// }

void	philo_log(t_philo *philo, const char *action)
{
	semaphore_report(sem_wait, philo->data->sem_log);
	printf("%ld %d %s\n", pl_time() - philo->data->creation_time,
		philo->id, action);
	if (ft_strcmp(action, DEAD))
		semaphore_report(sem_post, philo->data->sem_log);
	// semaphore_report(sem_post, philo->data->sem_log);
}

void	philo_do(t_philo *philo, int time)
{
	time_t	start;

	(void)philo;
	start = pl_time();
	while (pl_time() - start < time)
		usleep (250);
}
