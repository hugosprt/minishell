/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpol <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 02:54:18 by rpol              #+#    #+#             */
/*   Updated: 2021/12/02 09:21:30 by rpol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	intlen(int n)
{
	size_t	len;

	len = 0;
	if (n < 0)
		n *= -1;
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static size_t	sign(int *n)
{
	if (*n < 0)
	{
		*n *= -1;
		return (1);
	}
	return (0);
}

char	*ft_itoa(int n)
{
	size_t	len;
	int		tmp;
	char	*s;

	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	tmp = n;
	len = intlen(n) + sign(&n);
	s = malloc(sizeof(char) * (len + 1));
	if (!s)
		return (NULL);
	s[len--] = '\0';
	while (n > 0)
	{
		s[len--] = '0' + (n % 10);
		n /= 10;
	}
	if (tmp < 0)
		s[0] = '-';
	return (s);
}
