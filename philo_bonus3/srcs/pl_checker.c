/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pl_checker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichan <yichan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 01:47:16 by yichan            #+#    #+#             */
/*   Updated: 2023/05/01 01:56:47 by yichan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*pl_checker(void *arg)
{
	t_philo	*philo;

	philo = arg;
	while ((pl_time() - philo->last_meal) < philo->data->tm_die)
		usleep(500 / 2);
	philo_log(philo, DEATH);
	exit(1);
	return (NULL);
}