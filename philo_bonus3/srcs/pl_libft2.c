/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pl_libft2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichan <yichan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 15:42:11 by yichan            #+#    #+#             */
/*   Updated: 2023/05/03 04:04:54 by yichan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// int	ft_atoi(const char *str)
// {
// 	long int	result;
// 	int			sign;

// 	result = 0;
// 	sign = 1;
// 	while ((*str >= '\t' && *str <= '\r') || *str == ' ')
// 		str ++;
// 	if (*str == '+' || *str == '-')
// 	{
// 		if (*str++ == '-')
// 			sign *= -1;
// 	}
// 	while (ft_isdigit(*str))
// 	{
// 		result = result * 10 + (*str++ - '0');
// 		if (result * sign > 2147483647)
// 			return (-1);
// 		if (result * sign < -2147483648)
// 			return (0);
// 	}
// 	return (sign * result);
// }

// void	ft_derefliter(t_list *lst, void (*f)(void *), char *deref)
// {
// 	t_list	*temp;

// 	temp = lst;
// 	if (!lst || !f)
// 		return ;
// 	while (temp)
// 	{
// 		f(temp->deref);
// 		temp = temp->next;
// 	}
// }