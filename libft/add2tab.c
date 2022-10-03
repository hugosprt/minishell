/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add2tab.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpol <rpol@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:47:42 by rpol              #+#    #+#             */
/*   Updated: 2022/10/03 13:47:48 by rpol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_n_arg(char **t)
{
	int	n;

	n = 0;
	if (!t)
		return (n);
	while (t[n])
		n++;
	return (n);
}

static void	ft_free(char **t)
{
	int	i;

	i = 0;
	while (t[i])
	{
		free(t[i]);
		i++;
	}
	free(t[i]);
}

char	**add2tab(char **t, char *s)
{
	int		i;
	char	**sa;

	i = 0;
	if (!s)
		return (t);
	i = check_n_arg(t);
	sa = malloc(sizeof(char *) * (i + 1));
	if (!sa)
		return (NULL);
	sa[i + 1] = NULL;
	sa[i] = ft_strdup(s);
	if (!t)
		return (sa);
	i--;
	while (i >= 0)
	{
		sa[i] = ft_strdup(t[i]);
		i--;
	}
	ft_free(t);
	return (sa);
}
