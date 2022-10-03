/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   joinfree1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpol <rpol@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:47:00 by rpol              #+#    #+#             */
/*   Updated: 2022/10/03 13:47:03 by rpol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*joinfree1(char *s1, char *s2)
{
	char	*s3;
	int		i;
	int		j;

	if (!s1)
		return (ft_strdup(s2));
	s3 = (char *) malloc(ft_strlen(s1) + ft_strlen(s2) + 2 * (sizeof (char)));
	if (s3 == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		s3[i] = s1[i];
		i++;
	}
	free(s1);
	s3[i++] = '*';
	while (s2[j])
	{
		s3[i + j] = s2[j];
		j++;
	}
	s3[i + j] = '\0';
	return (s3);
}

char	*joinfree2(char *s1, char *s2)
{
	char	*s3;
	int		i;
	int		j;

	if (!s1)
		return (ft_strdup(s2));
	s3 = (char *) malloc(ft_strlen(s1) + ft_strlen(s2) + 2 * (sizeof (char)));
	if (s3 == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		s3[i] = s1[i];
		i++;
	}
	free(s1);
	while (s2[j])
	{
		s3[i + j] = s2[j];
		j++;
	}
	s3[i + j] = '\0';
	return (s3);
}
