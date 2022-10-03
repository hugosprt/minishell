/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpol <rpol@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:40:44 by rpol              #+#    #+#             */
/*   Updated: 2022/10/03 13:43:46 by rpol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	incr(int *i, int *r, char **ret, int n)
{
	if (n == 2)
	{
		*i += 1;
		*r = 0;
	}
	if (n == 1)
	{
		ret[0] = NULL;
		ret[1] = NULL;
	}
}

int	is_equal(char c, char charset)
{
	if (charset == c)
		return (1);
	return (0);
}

char	*ft_strcpy2(char const *s, int *i, int size)
{
	int		j;
	char	*ret;

	j = 0;
	ret = (char *) malloc(sizeof(char) * (size + 1));
	if (ret == NULL)
		return (NULL);
	while (j < size)
	{
		ret[j] = s[*i];
		*i = *i + 1;
		j++;
	}
	ret[j] = 0;
	return (ret);
}

char	**ft_free_equal(char **ret, int k)
{
	while (k >= 0)
	{
		free(ret[k]);
		k--;
	}
	free(ret);
	return (NULL);
}

char	**ft_trim_equal2(char const *s, char charset, int r, char **ret)
{
	int		j;
	int		i;
	int		k;

	i = 0;
	k = -1;
	incr(&i, &r, ret, 1);
	while (s[i])
	{
		if (s[i] != charset)
		{
			j = i;
			if (r == 0)
				charset = 127;
			r++;
			while (s[j] != charset && s[j])
				j++;
			ret[++k] = ft_strcpy2(s, &i, j - i);
			if (!ret[k])
				return (ft_free_equal(ret, k));
		}
		else
			incr(&i, &r, ret, 2);
	}
	return (ret);
}
