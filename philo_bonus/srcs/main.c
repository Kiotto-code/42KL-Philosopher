/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichan <yichan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 19:11:53 by yichan            #+#    #+#             */
/*   Updated: 2023/04/23 20:00:51 by yichan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	initialize(t_data *data, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (err_msg("WRONG_COUNT_OF_ARGUMENTS"));
	data->num_phls = ft_atoi(argv[1]);
	data->tm_die = ft_atoi(argv[2]);
	data->tm_eat = ft_atoi(argv[3]);
	data->tm_sleep = ft_atoi(argv[4]);
	data->mealtarget = 0;
	data->creation_time = 0;
	if (data->num_phls < 1 || data->tm_die < 1 || data->tm_eat < 1 \
		|| data->tm_sleep < 1)
		return (err_msg("WRONG_ARGUMENT"));
	if (argc == 6)
	{
		data->mealtarget = ft_atoi(argv[5]);
		if (data->mealtarget < 1)
			return (err_msg("WRONG_ARGUMENT"));
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (err_msg("MALLOC_ERROR"));
	if (initialize(data, argc, argv) != 0)
	{
		free(data);
		return (1);
	}
	if (philosophers(data) != 0)
	{
		free(data);
		return (1);
	}
	free(data);
	return (0);
}
