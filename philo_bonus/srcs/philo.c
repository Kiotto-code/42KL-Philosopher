/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichan <yichan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 19:11:58 by yichan            #+#    #+#             */
/*   Updated: 2023/04/13 20:27:28 by yichan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

// void	sem_opener(t_data *data)
// {
// 	if (sem_unlink("print_sem") == -1)
// 		exit(1);
// 	if (sem_unlink("fork"))
// 		exit(1);
// 	sem_unlink("print_sem");
// 	sem_unlink("fork");
// 	data->print_sem = sem_open("print_sem", O_CREAT, 0644, 1);
// 	data->fork = sem_open("fork", O_CREAT, 0644, data->num_phls);
// 	if (data->print_sem == 0 || data->fork == 0)
// 		exit(1);
// }
void	sem_opener(t_data *data)
{
	sem_unlink("print_sem");
	sem_unlink("fork");
	data->print_sem = sem_open("print_sem", O_CREAT, 0644, 1);
	data->fork = sem_open("fork", O_CREAT, 0644, data->num_phls);
	if (data->print_sem == 0 || data->fork == 0)
		exit(1);
}

void	sem_closer(t_data *data)
{
	if (sem_close(data->print_sem))
		exit(1);
	if (sem_unlink("print_sem") == -1)
		exit(1);
	if (sem_close(data->fork))
		exit(1);
	if (sem_unlink("fork"))
		exit(1);
}

int	philo_create_and_start(t_philo *phls, t_data *data)
{
	int	it;

	data->creation_time = get_time();
	it = 0;
	while (it < data->num_phls)
	{
		phls[it].pid = fork();
		if (phls[it].pid == -1)
			return (err_msg(FORK_ERROR));
		if (phls[it].pid == 0)
		{
			phls[it].id = it + 1;
			phls[it].data = data;
			if (data->notepme > 0)
			{
				phls[it].num_meals = 0;
				phls[it].satiety = 0;
			}
			phls_life((void *)&phls[it]);
		}
		it++;
	}
	return (0);
}

int	philosophers(t_data *data)
{
	t_philo	*phls;
	int		it;

	it = 0;
	phls = (t_philo *)malloc(sizeof(t_philo) * data->num_phls);
	if (!phls)
		return (1);
	sem_opener(data);
	if (philo_create_and_start(phls, data) != 0)
		return (1);
	if (waitpid(-1, NULL, 0) == -1)
		return (1);
	while (it < data->num_phls)
	{
		kill(phls[it].pid, SIGKILL);
		it++;
	}
	sem_closer(data);
	free(phls);
	return (0);
}
