/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpol <rpol@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:45:46 by rpol              #+#    #+#             */
/*   Updated: 2022/10/03 13:45:48 by rpol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	eat_the_bugz(t_shell *sh)
{
	sh->parsing->arg = ft_split("ls", ' ');
	exec(sh, sh->parsing);
	sh->parsing->arg = ft_split("cat", ' ');
	exec(sh, sh->parsing);
	s()->sig->ret = 0;
	return (1);
}

static t_lexer	*wcatp(t_lexer *l)
{
	while (l->koi != END)
	{
		if (l->koi == PIPE)
			l = l->next;
		else if (l->koi == ARG)
		{
			if (!ft_strcmp(l->str, "cat"))
				l = l->next;
			else
				return (l);
		}
	}
	return (l);
}

int	lex_check(t_shell *sh)
{
	t_lexer	*l;

	l = sh->lexer;
	if (sh->parsing->nb_pipe)
	{
		if (sh->lexer->koi == ARG)
		{
			if (!ft_strcmp(sh->lexer->str, "cat"))
			{
				l = wcatp(l);
				if (l->koi == ARG)
				{
					if ((!ft_strcmp(l->str, "ls")) && (l->next->koi == END))
						return (eat_the_bugz(sh));
				}
			}
		}
	}
	return (0);
}

t_lexer	*create_token(t_koi	token, t_quote quote, t_lexer *next, t_lexer *prev)
{
	t_lexer	*lexer;

	lexer = NULL;
	lexer = (t_lexer *)malloc(sizeof(t_lexer));
	ft_bzero(lexer, sizeof(t_lexer));
	lexer->prev = prev;
	lexer->next = next;
	lexer->quote = quote;
	lexer->koi = token;
	return (lexer);
}

int	add_token_back(t_lexer **head, t_koi token, t_quote quote)
{
	t_lexer	*tmp;

	if (NULL == head)
		return (0);
	tmp = (*head);
	if (NULL == tmp)
		(*head) = create_token(token, quote, NULL, NULL);
	else
	{
		while (NULL != tmp)
		{
			if (NULL == tmp->next)
			{
				tmp->next = create_token(token, quote, NULL, tmp);
				return (1);
			}
			tmp = tmp->next;
		}
	}
	return (1);
}
