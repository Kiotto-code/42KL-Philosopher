/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichan <yichan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 22:24:21 by yichan            #+#    #+#             */
/*   Updated: 2023/02/11 22:24:21 by yichan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

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

# define L_FORK_TAKEN	1
# define R_FORK_TAKEN	2
# define EATING			3
# define SLEEPING		4
# define THINKING		5
# define DIED			6

typedef struct s_data
{
	pid_t			*num_pid;
	stuct s_philo	*philo;
	int				num_phls;
	int				tm_die;
	int				tm_eat;
	int				tm_sleep;
	int				mealtarget;
	long			creation_time;
	sem_t			*fork;
	sem_t			*print_sem;
}	t_data;

typedef struct s_philo
{
	t_data	*data;
	pid_t	pid;
	int		id;
	int		num_meals;
	int		satiety;
	long	last_meal;
	sem_t	*lmeal_rec;
}	t_philo;

// i

sem_t	*create_sem(const char *name, int count, uint32_t mode, int value);

#endif