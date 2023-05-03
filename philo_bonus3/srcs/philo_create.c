/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichan <yichan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 18:05:19 by yichan            #+#    #+#             */
/*   Updated: 2023/05/04 05:44:12 by yichan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

char	*pl_semname(const char *str, int id)
{
	char	*res;
	char	*temp;

	temp = ft_itoa(id);
	res = ft_strjoin(str, temp);
	// free(str);
	free(temp);
	return (res);
}

void	pl_philorun(t_data *record)
{
	int		i;

	i = -1;
	while (++i < record->num_phls)
	{
		record->num_pid[i] = fork();
		if (record->num_pid[i] == -1)
			printf("Fork error at index: %d\n", i);
		else if (record->num_pid[i] == 0)
			philo_simulation(&record->philo[i]);
	}
}

// void	pl_philoinit(t_data *record)
// {
// 	// t_data	*temp;
// 	t_philo	*phl_create;
// 	char	*sem_name;
// 	int		i;
	
// 	// temp = 0;
// 	i = -1;
// 	while (++i < record->num_phls)
// 	{
// 		// temp = record.philo;
// 		phl_create = ft_calloc(sizeof(t_philo));
// 		phl_create->id = i +1;
// 		phl_create->num_meals = 0;
// 		sem_name = pl_semname("lmeal_rec", phl_create->id);
// 		phl_create->lmeal_rec = create_sem(sem_name, O_CREAT | O_EXCL, 0660, 1);
// 		// printf("phl_create lmeal_rec: %p\n", phl_create->lmeal_rec);
// 		free(sem_name);
// 		phl_create->data = record;
// 		record->philo[i] = *phl_create;
// 		// printf("philo id: %d\n", record->philo[i].id);
// 		// printf("philo lmeal_rec: %p\n", record->philo[i].lmeal_rec);
// 		phl_create = 0;
// 		// free(phl_create);
// 		// phl_create.lmeal_rec = record.creation_time;
// 	}
// }

void	pl_philoassign(t_data *record, int i)
{
	t_philo	phl_create;
	char	*sem_name;

	// phl_create = ft_calloc(sizeof(t_philo));
	phl_create.id = i +1;
	phl_create.num_meals = 0;
	sem_name = pl_semname("lmeal_rec", phl_create.id);
	phl_create.lmeal_rec = create_sem(sem_name, O_CREAT | O_EXCL, 0660, 01);
	free(sem_name);
	phl_create.data = record;
	(record->philo)[i] = phl_create;
	// phl_create = 0;
}


void	pl_philoinit(t_data *record)
{
	// t_data	*temp;
	// t_philo	*phl_create;
	// char	*sem_name;
	int		i;
	
	// temp = 0;
	i = -1;
	while (++i < record->num_phls)
	{
		pl_philoassign(record, i);
		// temp = record.philo;
		// phl_create = ft_calloc(sizeof(t_philo));
		// phl_create->id = i +1;
		// phl_create->num_meals = 0;
		// sem_name = pl_semname("lmeal_rec", phl_create->id);
		// phl_create->lmeal_rec = create_sem(sem_name, O_CREAT | O_EXCL, 0660, 01);
		// free(sem_name);
		// phl_create->data = record;
		// (record->philo)[i] = *phl_create;
		// phl_create = 0;
		// free(phl_create);
		// phl_create.lmeal_rec = record.creation_time;
	}
}