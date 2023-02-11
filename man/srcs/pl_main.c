/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pl_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichan <yichan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 15:21:49 by yichan            #+#    #+#             */
/*   Updated: 2023/02/01 15:21:49 by yichan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_value(int n)
{
	if (n < 1)
		return (err_display("arg value not greater than 0\n"));
	return (0);
}

int check_digit(int ac, char**av)
{
	int i;
	// int j;

	i = 0;
	while (++i < ac)
	{
		if (ft_atoi(av[i]) == -1)
		{
			printf("Wrong Argument Input\n");
			return (1);
		}
	}
	return (0);
}


int	check_argument(int ac, char **av, t_book *record)
{
	int	i;

	if (check_digit(ac, av) == 1)
		return (1);
	i = 0;
	while (av[++i])
	{
		if (check_value(ft_atoi(av[i])) == 1)
			return (1);
	}
	if (!(ac > 4 && ac < 7))
	{
		err_display ("Wrong argument");
		return (1);
	}
	record->pl_num = ft_atoi(av[1]);
	record->time_to_die = ft_atoi(av[2]);
	record->time_to_eat = ft_atoi(av[3]);
	record->time_to_sleep = ft_atoi(av[4]);
	record->end = 0;
	record->full_counter = 0;
	record->meal_target = -1;
	// printf("record->time_to_die: %d", record->time_to_die);
	if (ac == 6)
		record->meal_target = ft_atoi(av[5]);
	// printf("meal_target %ld \n", record->meal_target);
	printf("%ld \n", record->pl_num);
	printf("%ld \n",record->time_to_die);
	printf("%ld \n",record->time_to_eat);
	printf("%ld \n",record->time_to_sleep);
	printf("%ld \n",record->end);
	printf("%ld \n",record->full_counter);
	printf("%ld \n",record->meal_target);
	return (0);
}

int	main(int ac, char *av[])
{
	t_book		record;
	// pthread_t	thread;

	if (check_argument(ac, av, &record) == 1)
		return (1);
	philo(&record);
	// free (&record);
	// memset(&record, 0, sizeof(t_book));
	// system("leaks -q philo");
	return (0);
}
