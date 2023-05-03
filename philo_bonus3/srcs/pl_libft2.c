/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pl_libft2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichan <yichan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 15:42:11 by yichan            #+#    #+#             */
/*   Updated: 2023/05/03 04:14:07 by yichan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	int		a;
	int		b;
	char	*res;

	a = ft_strlen(s1);
	b = 0;
	res = (char *)malloc (a + 1);
	if (res == NULL)
		return (NULL);
	while (b < a)
	{
		res[b] = s1[b];
		b++;
	}
	res[b] = '\0';
	return (res);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	char	*ptr;

	if (!s1 || !s2)
		return (NULL);
	res = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!res)
		return (NULL);
	ptr = res;
	while (*s1)
		*res++ = *s1++;
	while (*s2)
		*res++ = *s2++;
	*res = '\0';
	return (ptr);
}

static size_t	count(int n)
{
	size_t	i;

	i = 0;
	while (n)
	{
		n /= 10;
		i ++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char		*res;
	size_t		i;
	long int	nb;

	nb = n;
	i = count(nb);
	if (n < 0)
	{
		nb = -nb;
		i += 1;
	}
	if (n == 0)
		return (ft_strdup("0"));
	res = (char *)malloc(sizeof(char) * (i + 1));
	if (!res)
		return (NULL);
	res[i] = '\0';
	while (i--)
	{
		res[i] = (nb % 10) + '0';
		nb = nb / 10;
	}
	if (n < 0)
		res[0] = '-';
	return (res);
}