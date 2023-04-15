/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichan <yichan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 19:11:48 by yichan            #+#    #+#             */
/*   Updated: 2023/04/16 01:32:58 by yichan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	eating_or_sleeping(long time)
{
	long	start;
	long	stop;

	start = get_time();
	stop = start + time;
	while (stop > start)
	{
		usleep(50);
		start = get_time();
	}
}

void	philo_sleeping(t_philo *phls)
{
	phls_msg(SLEEPING, get_time() - phls->data->creation_time, \
				phls->id, phls->data->print_sem);
	eating_or_sleeping(phls->data->tm_sleep);
}

void	philo_eating(t_philo *phls)
{
	phls_msg(EATING, get_time() - phls->data->creation_time, \
				phls->id, phls->data->print_sem);
	phls->last_meal = get_time();
	eating_or_sleeping(phls->data->tm_eat);
	sem_post(phls->data->fork);
	sem_post(phls->data->fork);
	if (phls->data->mealtarget > 0)
	{
		phls->num_meals++;
		if (phls->num_meals >= phls->data->mealtarget)
			phls->satiety = 1;
	}
}

void	philo_takes_forks(t_philo *phls)
{
	sem_wait(phls->data->fork);
	phls_msg(L_FORK_TAKEN, get_time() - phls->data->creation_time, \
				phls->id, phls->data->print_sem);
	sem_wait(phls->data->fork);
	phls_msg(R_FORK_TAKEN, get_time() - phls->data->creation_time, \
				phls->id, phls->data->print_sem);
}

void	phls_life(void *phls_void)
{
	t_philo	*phls;
	char	*philo_id;
	char	*sem_name;

	phls = (t_philo *)phls_void;
	phls->last_meal = get_time();
	phls->num_meals = 0;
	philo_id = ft_itoa(phls->id);
	sem_name = ft_strjoin("lmeal_rec", philo_id);
	create_sem(phls->lmeal_rec, sem_name, 1);
	free(philo_id);
	free(sem_name);
	if (!(phls->id % 2))
		usleep(500);
	if (philo_checker(phls) != 0)
		exit (1);
	while (1)
	{
		philo_takes_forks(phls);
		philo_eating(phls);
		philo_sleeping(phls);
		phls_msg(THINKING, get_time() - phls->data->creation_time, phls->id, \
					phls->data->print_sem);
	}
}
