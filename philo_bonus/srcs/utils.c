/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichan <yichan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 19:12:03 by yichan            #+#    #+#             */
/*   Updated: 2023/04/25 17:31:22 by yichan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

sem_t	*create_sem(sem_t *sem, const char *name, int count)
{
	sem_t	*res;

	(void)sem;
	// sem_close(sem);
	sem_unlink(name);
	res = sem_open(name, O_CREAT, 0644, count);
	return (res);
}


void	ph_lmeal_rec(t_philo *phls)
{
	char	*philo_id;
	char	*sem_name;

	philo_id = ft_itoa(phls->id);
	sem_name = ft_strjoin("lmeal_rec", philo_id);
	// printf("sem_name = %s, philo_id = %s\n", sem_name, philo_id);
	// phls->lmeal_rec = create_sem(phls->lmeal_rec, sem_name, 1);
	phls->lmeal_rec = sem_open(sem_name, O_CREAT, 0644, 1);
	sem_unlink(sem_name);
	// printf("phls->lmeal_rec = %p\n", &(phls->lmeal_rec));
	if (phls->lmeal_rec == SEM_FAILED)
		exit (1);
	// sem_wait(phls->lmeal_rec);
	free(philo_id);
	free(sem_name);
}

int	ft_atoi(const char *str)
{
	int		in;
	int		sign;
	long	num;

	in = 0;
	sign = 1;
	num = 0;
	while ((((str[in] > 8) && (str[in] < 14)) || str[in] == 32) && \
			str[in] != '\0')
		in++;
	if (str[in] == 43 || str[in] == 45)
		sign = (str[in++] & 2) - 1;
	if (str[in] < 48 || str[in] > 57)
		return (0);
	while ((str[in] > 47) && (str[in] < 58))
		num = num * 10 + (str[in++] - '0');
	num = num * sign;
	if (num > 2147483647)
		return (-1);
	if (num < -2147483648)
		return (0);
	return ((int)num);
}

// int	err_msg(char *err)
// {
// 	printf ("%s\n", err);
// 	return (1);
// }

// void	phls_msg(int msg_code, long time, int id, sem_t *print_sem)
// {
// 	sem_wait(print_sem);
// 	if (msg_code == L_FORK_TAKEN)
// 		printf("%ld %d has taken a fork\n", time, id);
// 	else if (msg_code == R_FORK_TAKEN)
// 		printf("%ld %d has taken a fork\n", time, id);
// 	else if (msg_code == EATING)
// 		printf("%ld %d is eating\n", time, id);
// 	else if (msg_code == SLEEPING)
// 		printf("%ld %d is sleeping\n", time, id);
// 	else if (msg_code == THINKING)
// 		printf("%ld %d is thinking\n", time, id);
// 	else if (msg_code == DIED)
// 	{
// 		printf("%ld %d died\n", time, id);
// 		exit (1);
// 	}
// 	sem_post(print_sem);
// }

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
