/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichan <yichan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 17:58:53 by yichan            #+#    #+#             */
/*   Updated: 2023/05/02 17:07:55 by yichan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	if (argc < 5)
	{
		printf("More arguments required\n");
		printf("[num_phls][tm_die]"
			"[tm_eat][tm_sleep][mealtarget]\n");
	}
	else if (argc > 6)
		printf("Too many arguments\n");
	else
		return (philosopher(argv));
	return (1);
}
