/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpol <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 02:29:25 by rpol              #+#    #+#             */
/*   Updated: 2021/12/02 05:31:24 by rpol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t len)
{
	size_t	i;
	size_t	lendnd;
	size_t	lens;

	i = 0;
	lendnd = 0;
	lens = ft_strlen((char *)src);
	if (len == 0)
		return (lens);
	while (dest[lendnd] && lendnd < len)
		lendnd++;
	if (len == lendnd)
		return (len + lens);
	while (lendnd + i < len - 1 && src[i])
	{
		dest[i + lendnd] = src[i];
		i++;
	}
	dest[i + lendnd] = '\0';
	return (lendnd + lens);
}
