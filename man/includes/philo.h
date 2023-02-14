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

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdint.h>
# include <sys/time.h>
# include <unistd.h>
# include "philo.h"

// ◦ timestamp_in_ms X has taken a fork
// ◦ timestamp_in_ms X is eating
// ◦ timestamp_in_ms X is sleeping
// ◦ timestamp_in_ms X is thinking
// ◦ timestamp_in_ms X died

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIED "died"

	// long			pl_num;
	// long			time_to_die;
	// long			time_to_eat;
	// long			time_to_sleep;
	// long			meal_target;
// record

typedef struct s_book
{
	long			pl_num;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			meal_target;
	long			starttime;
	long			end;
	long			full_counter;
	pthread_mutex_t	*printer;
	pthread_mutex_t	*full_mut;
	pthread_mutex_t	*end_mut;
	void			*plptr;
}	t_book;

// philo struct
typedef struct s_thread
{
	t_book			*record;
	long			id;
	long			num_meals;
	long			fulfilled;
	long			last_meal;
	long			pl_num;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			meal_target;
	long			starttime;
	long			end;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
}	t_thread;

// pl_philo.c
int		philo(t_book *record);
int		pl_check_full(t_thread *pl, t_book *record);

// pl_init.c
int		pl_init_pl(t_thread *pl, pthread_mutex_t *action,
			pthread_mutex_t *fork, t_book *record);

// pl_error.c
int		err_display(char str[]);

// sl_libft.c
void	*ft_calloc(size_t count);
long	ft_atoi(const char *str);

// pl_mod_utils.c
void	pl_usleep(long num);
int		pl_show(t_thread *pl,
			char *msg, pthread_mutex_t *printer);
void	pl_show_run(unsigned int timestamp, int id,
			char *msg, pthread_mutex_t *printer);
void	*pl_checker(void *phls_void);
long	pl_time(void);

// pl_extra_func.c
int		meal_target_check(t_thread *pl, int *i, long current);
int		pl_eat(t_thread *pl, t_book	*record);
int		pl_sleep_think(t_thread *pl, t_book	*record);
void	pl_call_end(t_thread *pl);

#endif