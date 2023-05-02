/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichan <yichan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 22:24:21 by yichan            #+#    #+#             */
/*   Updated: 2023/02/11 22:24:21 by yichan           ###   ########.fr       */
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
# include <signal.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <semaphore.h>

// # define L_FORK_TAKEN	1
// # define R_FORK_TAKEN	2
// # define EATING			3
// # define SLEEPING		4
// # define THINKING		5
// # define DIED			6

# define GETFORK	"has taken a fork"
# define EAT		"is eating"
# define SLEEP		"is sleeping"
# define THINK		"is thinking"
# define DEAD		"died"


typedef struct s_data
{
	int				num_phls;
	int				tm_die;
	int				tm_eat;
	int				tm_sleep;
	int				mealtarget;
	long			creation_time;
	sem_t			*fork;
	sem_t			*sem_log;
	sem_t			*sem_end;
	pid_t			*num_pid;
	struct s_philo	*philo;
	// sem_t			*print_sem;
}	t_data;

typedef struct s_philo
{
	t_data	*data;
	// t_data	*record;
	// pid_t	pid;
	int		id; //id
	int		num_meals;//meals eaten
	long	last_meal;
	sem_t	*lmeal_rec;//lmeal_rec//sem
	// int		satiety;
}	t_philo;

// i

int		philosopher(char **argv);
sem_t	*create_sem(const char *name, int count, uint32_t mode, int value);
int		philo_create_and_start(t_data *record);
void	pl_philoinit(t_data *record);
void	pl_philorun(t_data *record);
void	*pl_checker(void *arg);
void	philo_simulation(t_philo *philo);
void	semaphore_report(sem_t sem_func(sem_t *), sem_t *sem);
long	pl_time(void);
void	pl_lmeal_time(t_philo *philo);
void	philo_log(t_philo *philo, const char *action);
void	philo_do(t_philo *philo, int time);
int		philo_check(char **av);
int		err_print(char *str, int status);
long	ft_atoi(const char *str);

#endif
