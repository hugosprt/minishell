/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hspriet <hspriet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:41:38 by rpol              #+#    #+#             */
/*   Updated: 2022/10/05 14:28:45 by hspriet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_empty(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

void	skip_white_space(t_shell *s)
{
	while (*s->prompt && is_empty(*s->prompt))
	{
		s->prompt++;
	}
}

void	add_token_pip(t_shell *s)
{
	add_token_back(&s->lexer, PIPE, NOT_YET);
	s->prompt++;
}

void	add_token_rr(t_shell *s)
{
	if (s->prompt[1] == '>')
	{
		add_token_back(&s->lexer, RR_REDIR, NOT_YET);
		s->prompt += 2;
	}
	else
	{
		add_token_back(&s->lexer, R_REDIR, NOT_YET);
		s->prompt += 1;
	}
}

void	add_token_lr(t_shell *s)
{
	if (s->prompt[1] == '<')
	{
		add_token_back(&s->lexer, LL_REDIR, NOT_YET);
		s->prompt += 2;
	}
	else
	{
		add_token_back(&s->lexer, L_REDIR, NOT_YET);
		s->prompt += 1;
	}
}
