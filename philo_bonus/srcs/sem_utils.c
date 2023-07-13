/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichan <yichan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:47:55 by yichan            #+#    #+#             */
/*   Updated: 2023/07/13 10:38:49 by yichan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

//		if O_CREAT is specified in oflag, then the
//		semaphore is created if it does not already exist.  The owner
//		(user ID) of the semaphore is set to the effective user ID of the
//		calling process.  The group ownership (group ID) is set to the
//		effective group ID of the calling process.  If both O_CREAT and
//		O_EXCL are specified in oflag, then an error is returned if a
//		semaphore with the given name already exists.

//O_EXCL	// When you're creating a new named semaphore, O_EXCL causes
			// sem_open() to fail if a semaphore with sem_name already
			// exists. Without O_EXCL, sem_open() attaches to an existing
			// semaphore or creates a new one if sem_name doesn't exist.

sem_t	*create_sem(const char *name, int count, uint32_t mode, int value)
{
	sem_t	*res;

	(void)count;
	sem_unlink(name);
	res = sem_open(name, O_CREAT | O_EXCL, mode, value);
	if (res == SEM_FAILED)
		printf("Failed to open sem: %s\n", name);
	else
		sem_unlink(name);
	return (res);
}

void	semaphore_report(sem_t ft(sem_t *), sem_t *sem)
{
	const char	*ftname;
	int			value;

	value = ft(sem);
	if (value == 0)
		return ;
	else if (ft == sem_wait)
		ftname = "sem_wait";
	else if (ft == sem_post)
		ftname = "sem_post";
	else if (ft == sem_close)
		ftname = "sem_close";
	else
		ftname = "undefined_function";
	printf("semaphore_report: %s(%p) returned: %d\n", ftname, sem, value);
}

//time_get
long	pl_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

//set last meal time
void	pl_lmeal_time(t_philo *philo)
{
	long temp;
	
	// semaphore_report(sem_wait, philo->lmeal_rec);
	// time_set(&philo->time_lastmeal);
	// philo->last_meal = 	time_get(&philo->time_lastmeal);
	// temp = 	time_get(&philo->time_lastmeal);
	temp = 	pl_time();
	philo->last_meal = 	temp;
	philo->check_meal = time_get(&philo->time_lastmeal);
	// semaphore_report(sem_post, philo->lmeal_rec);
}

// time_t	time_get(t_time *time)
// {
// 	time_t	status;

// 	// semaphore_report(sem_wait, time->sem);
// 	// time_set(time);
// 	// status = (time->s_time.tv_sec) * 1000
// 		+ (time->s_time.tv_usec) / 1000;
// 	// semaphore_report(sem_post, time->sem);
// 	return (status);
// }

time_t	time_get(t_time *time)
{
	time_t	status;

	// semaphore_report(sem_wait, time->sem);
	gettimeofday(&time->s_time, NULL);
	status = (time->s_time.tv_sec) * 1000
		+ (time->s_time.tv_usec) / 1000;
	// semaphore_report(sem_post, time->sem);
	return (status);
}


void	time_set(t_time *time)
{
	// semaphore_report(sem_wait, time->sem);
	gettimeofday(&time->s_time, NULL);
	// semaphore_report(sem_post, time->sem);
}