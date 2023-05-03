/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichan <yichan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:47:55 by yichan            #+#    #+#             */
/*   Updated: 2023/05/04 05:40:46 by yichan           ###   ########.fr       */
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
	// res = sem_open(name, O_CREAT | O_EXCL, mode, value);
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
	// printf("pl_time: %ld\n", time.tv_sec * 1000 + time.tv_usec / 1000);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

//set last meal time
void	pl_lmeal_time(t_philo *philo)
{
	// sem_wait(philo->lmeal_rec);
	// printf("philo?? id: %d\n", philo->id);
	// printf("philo->lmeal_rec: %d\n", *philo->lmeal_rec);
	// printf("check\n");
	semaphore_report(sem_wait, philo->lmeal_rec);
	philo->last_meal = pl_time();
	// sem_post(philo->lmeal_rec);
	semaphore_report(sem_post, philo->lmeal_rec);
}
