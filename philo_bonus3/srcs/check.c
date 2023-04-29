/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichan <yichan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 18:35:15 by yichan            #+#    #+#             */
/*   Updated: 2023/04/27 19:09:00 by yichan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_digit(char*av)
{
	while (av++)
		if (*av <= '0' && *av >= '9')
			return (0);
	return (1);
}

static int	philo_criteria(char *str)
{
	int nbr;

	nbr = ft_atoi(str);
	if (nbr == 0)
		return (err_print("number could not be 0\n", 0));
	else if (*str == 0)
		return (err_print("argument could not be empty\n", 0));
	else if (nbr < 0)
		return (err_print("number could not be negative\n", 0));
	else if (check_digit(str) == 0)
		return (err_print("argument could not be non-digit\n", 0));
	else
		return (1);
}

int	philo_check(char **av)
{
	int	i;
	int	status;

	status = 1;
	i = -1;
	while (av[++i] && i < 5 && status == 1)
	{
		status = philo_criteria(av[1]);
	}
	return (status);
}