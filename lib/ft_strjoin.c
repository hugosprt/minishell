/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpol <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 02:51:25 by rpol              #+#    #+#             */
/*   Updated: 2021/12/02 23:36:53 by rpol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t		i;
	size_t		lens1;
	size_t		lens2;
	char		*news;

	i = 0;
	lens1 = strlen((char *)s1);
	lens2 = strlen((char *)s2);
	news = malloc(sizeof(char) * (lens1 + lens2 + 1));
	if (!news)
		return (NULL);
	while (i < (lens1 + lens2))
	{
		if (i < lens1)
			news[i] = s1[i];
		else
			news[i] = s2[(i - lens1)];
		i++;
	}
	news[i] = '\0';
	return (news);
}
