/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichan <yichan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 21:26:27 by yichan            #+#    #+#             */
/*   Updated: 2023/04/23 21:34:17 by yichan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	err_msg(char *err)
{
	printf ("%s\n", err);
	return (1);
}

void	phls_msg(int msg_code, long time, int id, sem_t *print_sem)
{
	sem_wait(print_sem);
	if (msg_code == L_FORK_TAKEN)
		printf("%ld %d has taken a fork\n", time, id);
	else if (msg_code == R_FORK_TAKEN)
		printf("%ld %d has taken a fork\n", time, id);
	else if (msg_code == EATING)
		printf("%ld %d is eating\n", time, id);
	else if (msg_code == SLEEPING)
		printf("%ld %d is sleeping\n", time, id);
	else if (msg_code == THINKING)
		printf("%ld %d is thinking\n", time, id);
	else if (msg_code == DIED)
	{
		printf("%ld %d died\n", time, id);
		exit (1);
	}
	sem_post(print_sem);
}