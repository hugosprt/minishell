/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpol <rpol@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:41:57 by rpol              #+#    #+#             */
/*   Updated: 2022/10/08 16:05:25 by rpol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_token(t_shell *s)
{
	if (*s->prompt == '|')
		add_token_pip(s);
	else if (*s->prompt == '>')
		add_token_rr(s);
	else if (*s->prompt == '<')
		add_token_lr(s);
	else if (!is_separator(*s->prompt))
		add_token_arg(s);
}

int	lexer(t_shell *s)
{
	char	*tmp;

	tmp = s->prompt;
	if (s->prompt == NULL)
		return (1);
	while (*s->prompt != '\0' && !s->error)
	{
		if (is_empty(*s->prompt))
			skip_white_space(s);
		else
			add_token(s);
	}
	add_token_back(&s->lexer, END, NOT_YET);
	index_quotes(s);
	if (!s->error)
	{	
		s->prompt = (char *)tmp;
		first_arg(s, s->lexer);
	}
	free(tmp);
	return (1);
}
