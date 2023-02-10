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


typedef struct s_book
{
	int	pl_num;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	meal_target;
	long starttime;
	int	end;
	int full_counter;
	pthread_mutex_t	*printer;
	void *plptr;
	// int pl_act;
} t_book;

typedef struct s_thread
{
	t_book			*record;
	int				id;
	int				num_meals;
	int				fulfilled;
	long			last_meal;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
}	t_thread;

// pl_philo.c
int		philo(t_book *record);
int		pl_check_full(t_thread *pl, t_book *record);

// pl_init.c
int		pl_init_pl(t_thread *pl, pthread_mutex_t *action, pthread_mutex_t *fork, t_book *record);

// pl_error.c
int		err_display(char str[]);

// sl_libft.c
void	*ft_calloc(size_t count);
int		ft_atoi(const char *str);

// pl_mod_utils.c
void	pl_usleep(long num);
void	pl_show(unsigned timestamp, t_thread *pl, char *msg, pthread_mutex_t *printer);
void	pl_show_run(unsigned timestamp, int id, char *msg, pthread_mutex_t *printer);

// void		pl_show(unsigned timestamp, t_thread *pl,
// 			char *msg, pthread_mutex_t *printer);
void	*pl_checker(void *phls_void);


// int	pl_show_run(unsigned timestamp, int id, char *msg, pthread_mutex_t *printer);
long	pl_time(void);










#endif