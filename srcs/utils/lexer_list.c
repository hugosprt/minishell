/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hspriet <hspriet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:45:46 by rpol              #+#    #+#             */
/*   Updated: 2022/10/09 14:30:47 by hspriet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	lex_check(t_shell *sh)
{
	if (isp(sh))
		return (1);
	return (0);
}

t_lexer	*create_token(t_koi	token, t_quote quote, t_lexer *next, t_lexer *prev)
{
	t_lexer	*lexer;

	lexer = NULL;
	lexer = (t_lexer *)malloc(sizeof(t_lexer));
	if (lexer == NULL)
		return (NULL);
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
