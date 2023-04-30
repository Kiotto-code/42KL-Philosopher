/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichan <yichan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 18:26:43 by yichan            #+#    #+#             */
/*   Updated: 2023/05/01 00:26:46 by yichan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo_bonus.h"

/**
 * @brief Create a sem object
 * 	If you want to be sure you are creating a new (named) semaphore instead of opening an existing one 
 * 	then unlinking the name before the sem_open() call makes that pretty likely.
 * 
 * Calling sem_unlink() after sem_open() is not strictly necessary, but it can be a good practice to ensure
 * that the semaphore is properly cleaned up even if some process fails to call sem_close().
 * 
 * @param name 
 * @param count 
 * @param mode 
 * @param value	: initial value of the semaphore
 * @return sem_t* 
 */

int	philo_create_and_start(t_data *record)
{
	record->num_pid = malloc(sizeof(pid_t) * record->num_phls);
	record->philo = malloc(sizeof(t_philo) * record->num_phls);
	// philo_iter(piter_init_philo, record);
	pl_philoinit(record);
	// philo_iter(piter_init_sim, record);
	pl_philorun(record);
	philo_sim_status(record);
	// philo_iter(piter_clean_philo, record);
	waitpid(-1, NULL, 0);
	semaphore_report(sem_close, record->fork);
	semaphore_report(sem_close, record->sem_log);
	semaphore_report(sem_close, record->sem_end);
	free(record->num_pid);
	free(record->philo);
}

//		if O_CREAT is specified in oflag, then the
//		semaphore is created if it does not already exist.  The owner
//		(user ID) of the semaphore is set to the effective user ID of the
//		calling process.  The group ownership (group ID) is set to the
//		effective group ID of the calling process.  If both O_CREAT and
//		O_EXCL are specified in oflag, then an error is returned if a
//		semaphore with the given name already exists.

sem_t	*create_sem(const char *name, int count, uint32_t mode, int value)
{
	sem_t	*res;

	sem_unlink(name);
	res = sem_open(name, O_CREAT, mode, value);
	if (res == SEM_FAILED)
		return (res);
	sem_unlink(name);
	return (res);
}

void	record_init(t_data *record, char **argv)
{
	record->sem_end = create_sem("SEM_END", O_CREAT, 0644, 0);
	record->sem_log = create_sem("SEM_LOG", O_CREAT, 0644, 1);
	record->fork = create_sem("SEM_FORKS", O_CREAT, 0644, record->num_phls);
	record->num_phls = ft_atoi(argv[1]);
	record->tm_die = ft_atoi(argv[2]);
	record->tm_eat = ft_atoi(argv[3]);
	record->tm_sleep = ft_atoi(argv[4]);
	if (argv[5])
		record->num_eat = ft_atoi(argv[5]);
	else
		record->num_eat = -1;
}

int	philosopher(char **argv)
{
	t_data	record;

	if (!philo_check(argv + 1))
		return (1);
	record_init(&record, argv);
	if (record.sem_end == SEM_FAILED
		|| record.sem_log == SEM_FAILED
		|| record.forks == SEM_FAILED)
		return (1);
	philo_create_and_start(&record);
	return (0);
}
