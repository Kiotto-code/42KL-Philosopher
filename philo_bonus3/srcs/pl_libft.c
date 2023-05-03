/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pl_libft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichan <yichan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 18:59:59 by yichan            #+#    #+#             */
/*   Updated: 2023/05/03 04:22:45 by yichan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	it;

	it = 0;
	while (s1[it] && s2[it] && (s1[it] == s2[it]))
		it++;
	return ((unsigned char)s1[it] - (unsigned char)s2[it]);
}

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*copy;

	copy = (unsigned char *)s;
	while (n > 0)
	{
		copy[n -1] = c;
		n --;
	}
	return (s);
}

void	*ft_calloc(size_t count)
{
	void			*ptr;

	if (count >= SIZE_MAX)
		return (NULL);
	ptr = malloc(count);
	if (!ptr)
		return (NULL);
	ft_memset (ptr, 0, count);
	return (ptr);
}

int	ft_isdigit(int c)
{
	if ((c >= '0' && c <= '9'))
		return (1);
	return (0);
}

// long	pl_time(void)
// {
// 	struct timeval	time;

// 	gettimeofday(&time, NULL);
// 	return (time.tv_sec * 1000 + time.tv_usec / 1000);
// }

long	ft_atoi(const char *str)
{
	long int	result;
	long int	sign;

	result = 0;
	sign = 1;
	while ((*str >= '\t' && *str <= '\r') || *str == ' ')
		str ++;
	if (*str == '+' || *str == '-')
	{
		if (*str++ == '-')
			sign *= -1;
	}
	while (ft_isdigit(*str))
	{
		result = result * 10 + (*str++ - '0');
		if (result * sign > 2147483647)
			return (-1);
		if (result * sign < -2147483648)
			return (0);
	}
	if (*str != '\0')
		return (-1);
	return (sign * result);
}
