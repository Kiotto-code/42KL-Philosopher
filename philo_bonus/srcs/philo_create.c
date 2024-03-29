/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichan <yichan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 18:05:19 by yichan            #+#    #+#             */
/*   Updated: 2023/07/06 16:04:10 by yichan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

char	*pl_semname(const char *str, int id)
{
	char	*res;
	char	*temp;

	temp = ft_itoa(id);
	res = ft_strjoin(str, temp);
	free(temp);
	return (res);
}

void	pl_philorun(t_data *record)
{
	int		i;
	t_philo	*philo;

	philo = record->philo;
	i = -1;
	while (++i < record->num_phls)
	{
		record->num_pid[i] = fork();
		
		if (record->num_pid[i] == -1)
			printf("Fork error at index: %d\n", i);
		else if (record->num_pid[i] == 0)
		{
			char *sem_name = pl_semname("lmeal_rec", philo[i].id);
			philo[i].lmeal_rec = create_sem(sem_name, O_CREAT | O_EXCL, 0660, 01);
			free(sem_name);
			philo_simulation(&record->philo[i]);
		}
	}
}

void	pl_philoassign(t_data *record, int i)
{
	t_philo	phl_create;

	phl_create.id = i +1;
	phl_create.num_meals = 0;
	phl_create.data = record;
	(record->philo)[i] = phl_create;
}

void	pl_philoinit(t_data *record)
{
	int		i;

	i = -1;
	while (++i < record->num_phls)
	{
		pl_philoassign(record, i);
	}
}
