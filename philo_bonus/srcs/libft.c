/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichan <yichan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 18:59:59 by yichan            #+#    #+#             */
/*   Updated: 2023/04/16 01:27:53 by yichan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char const *s2)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	res = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) +1));
	if (!res)
		return (NULL);
	while (s1[i])
		res[i++] = s1[j++];
	j = 0;
	while (s2[j])
		res[i++] = s2[j++];
	res[i] = '\0';
	return (res);
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
