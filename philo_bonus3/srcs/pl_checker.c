/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pl_checker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichan <yichan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 01:47:16 by yichan            #+#    #+#             */
/*   Updated: 2023/05/03 03:59:38 by yichan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	piter_badend(unsigned int i, t_data *record)
{
	if (kill(record->num_pid[i], SIGINT) != -1)
		waitpid(record->num_pid[i], NULL, 0);
}

void	philo_sim_status(t_data *record)
{
	int  i;

	i = -1;
	waitpid(-1, NULL, 0);
	philo_iter(piter_badend, record);
	while (++i < record->num_phls)
	{
		record->num_pid[i] = fork();
		if (record->num_pid[i] == -1)
			return ;
		else if (record->num_pid[i] == 0)
			philo_simulation(&record->philo[i]);
	}
}


void	*pl_checker(void *arg)
{
	t_philo	*philo;

	philo = arg;
	while ((pl_time() - philo->last_meal) < philo->data->tm_die)
		usleep(500 / 2);
	philo_log(philo, DEAD);
	exit(1);
	return (NULL);
}