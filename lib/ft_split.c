/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpol <rpol@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 02:53:14 by rpol              #+#    #+#             */
/*   Updated: 2022/08/22 15:04:25 by rpol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_free(char **sa, size_t i)
{
	while (i > 0)
	{
		free(sa[i]);
		i--;
	}
	free(sa);
	return (NULL);
}

static size_t	check_n_of_words(const char *s, char sep)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = 0;
	while (s[i])
	{
		if (s[i] != sep && (s[i + 1] == sep || s[i + 1] == '\0'))
			n++;
		i++;
	}
	return (n);
}

static size_t	len_b_sep(char const *s, char sep)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != sep)
		i++;
	return (i);
}

char	**ft_split(char const *s, char c)
{
	size_t		i;
	char		**sa;

	i = 0;
	if (!s)
		return (NULL);
	sa = malloc(sizeof(char *) * (check_n_of_words(s, c) + 1));
	if (!sa)
		return (NULL);
	while (check_n_of_words(s, c))
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			sa[i] = ft_substr(s, 0, len_b_sep(s, c));
			if (!sa[i])
				return (ft_free(sa, i));
			i++;
		}
		while (*s && *s != c)
			s++;
	}
	sa[i] = NULL;
	return (sa);
}
