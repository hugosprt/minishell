/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpol <rpol@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:41:47 by rpol              #+#    #+#             */
/*   Updated: 2022/10/03 13:44:09 by rpol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_separator(char c)
{
	if (c == '|' || c == '>' || c == '<' || is_empty(c))
		return (1);
	return (0);
}

char	*ft_strldup(char *source, int size)
{
	char	*dest;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(source);
	dest = (char *) malloc(1 + len * sizeof(char));
	if (dest == NULL)
		return (NULL);
	while (i < len && i != size)
	{
		dest[i] = source[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	skip_double_quote(t_shell *s, int *i)
{
	(*i)++;
	s->prompt++;
	while (*s->prompt && *s->prompt != '\"')
	{
		(*i)++;
		s->prompt++;
	}
	if (*s->prompt)
	{
		(*i)++;
		s->prompt++;
	}
}

void	skip_single_quote(t_shell *s, int *i)
{
	(*i)++;
	s->prompt++;
	while (*s->prompt && *s->prompt != '\'')
	{
		(*i)++;
		s->prompt++;
	}
	if (*s->prompt)
	{
		(*i)++;
		s->prompt++;
	}
}

void	add_token_arg(t_shell *s)
{
	int			i;
	char		*tmp;
	t_lexer		*l;

	tmp = s->prompt;
	i = 0;
	add_token_back(&s->lexer, ARG, NOT_YET);
	while (*s->prompt && !is_separator(*s->prompt))
	{
		if (*s->prompt == '\'')
			skip_single_quote(s, &i);
		else if (*s->prompt == '\"')
			skip_double_quote(s, &i);
		else
		{
			i++;
			s->prompt++;
		}
	}
	l = find_last_elem2(s->lexer);
	l->str = ft_strldup(tmp, i);
}
