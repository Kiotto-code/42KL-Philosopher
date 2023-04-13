/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichan <yichan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 19:12:13 by yichan            #+#    #+#             */
/*   Updated: 2023/04/13 19:12:15 by yichan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/time.h>
# include <sys/wait.h>

# define WRONG_COUNT_OF_ARGUMENTS	-1
# define WRONG_ARGUMENT				-2
# define MALLOC_ERROR				-3
# define PTHREAD_ERROR				-4
# define FORK_ERROR					-5

# define L_FORK_TAKEN	1
# define R_FORK_TAKEN	2
# define EATING			3
# define SLEEPING		4
# define THINKING		5
# define DIED			6

typedef struct s_data
{
	int		num_phls;
	int		tm_die;
	int		tm_eat;
	int		tm_sleep;
	int		notepme;
	long	creation_time;
	sem_t	*fork;
	sem_t	*print_sem;
}	t_data;

typedef struct s_philo
{
	t_data	*data;
	pid_t	pid;
	int		id;
	int		num_meals;
	int		satiety;
	long	last_meal;
}	t_philo;

int		argv_processing(t_data *data, int argc, char **argv);
int		philosophers(t_data *data);
int		philo_create_and_start(t_philo *phls, t_data *data);
void	phls_life(void *phls);
void	philo_takes_forks(t_philo *phls);
void	philo_eating(t_philo *phls);
void	philo_sleeping(t_philo *phls);
void	eating_or_sleeping(long time);
int		philo_checker(t_philo *phls);
void	sem_opener(t_data *data);
void	sem_closer(t_data *data);

void	*life_checker(void *phls);
int		satiety_checker(t_philo *phls);

int		ft_atoi(const char *str);
int		err_msg(int err_number);
void	phls_msg(int msg_code, long time, int id, sem_t *print_sem);
long	get_time(void);

#endif