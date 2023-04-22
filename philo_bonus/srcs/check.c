/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichan <yichan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 19:11:41 by yichan            #+#    #+#             */
/*   Updated: 2023/04/17 03:52:56 by yichan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	satiety_checker(t_philo *phls)
{
	int	it;
	int	full_satiety;

	it = 0;
	full_satiety = 0;
	while (it < phls->data->num_phls)
	{
		full_satiety += phls->satiety;
		it++;
	}
	if (full_satiety >= phls->data->num_phls)
		return (1);
	return (0);
}

void	*life_checker(void *phls_void)
{
	int		it;
	t_philo	*phls;

	it = 0;
	phls = (t_philo *)phls_void;
	while (1)
	{
		if (phls->data->mealtarget > 0)
		{
			if (satiety_checker(phls) == 1)
				exit (0);
		}
		sem_wait(phls->lmeal_rec);
		if ((get_time() - phls->last_meal) > phls->data->tm_die)
		{
			phls_msg(DIED, get_time() - phls->data->creation_time, \
						phls->id, phls->data->print_sem);
			exit (0);
		}
		sem_post(phls->lmeal_rec);
		it++;
		usleep(100);
	}
	return (NULL);
}

int	philo_checker(t_philo *phls)
{
	pthread_t	checker;

	if (pthread_create(&checker, NULL, life_checker, (void *)phls) != 0)
		return (err_msg("PTHREAD_ERROR"));
	if (pthread_detach(checker) != 0)
		return (err_msg("PTHREAD_ERROR"));
	return (0);
}
