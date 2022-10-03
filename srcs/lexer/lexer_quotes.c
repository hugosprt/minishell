/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpol <rpol@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:41:18 by rpol              #+#    #+#             */
/*   Updated: 2022/10/03 13:41:19 by rpol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sing_quote(t_shell *s, char **str, t_lexer *l)
{
	(void) s;
	if (l->quote == S_QUOTES || l->quote == D_QUOTES)
		l->quote = MIX_QUOTES;
	else
		l->quote = S_QUOTES;
	(*str)++;
	while (**str != '\'' && **str != '\0')
		(*str)++;
	if (!(**str))
	{
		quote_problem(s, 0);
	}
	(*str)++;
}

void	doubl_quote(t_shell *s, char **str, t_lexer *l)
{
	(void) s;
	if (l->quote == S_QUOTES || l->quote == D_QUOTES)
		l->quote = MIX_QUOTES;
	else
		l->quote = D_QUOTES;
	(*str)++;
	while (**str != '\"' && **str != '\0')
		(*str)++;
	if (!(**str))
	{	
		quote_problem(s, 1);
	}
	(*str)++;
}

void	set_quote(t_shell *s, t_lexer *l)
{
	char	*str;

	str = l->str;
	while (!s->error && *str)
	{
		if (*str == '\'' && !s->error)
			sing_quote(s, &str, l);
		else if (*str == '\"' && !s->error)
			doubl_quote(s, &str, l);
		else
			str++;
	}
}

void	index_quotes(t_shell *s)
{
	t_lexer	*tmp;

	tmp = s->lexer;
	if (tmp == NULL)
		return ;
	while (tmp != NULL && !s->error)
	{
		if (tmp->koi == ARG)
			set_quote(s, tmp);
		tmp = tmp->next;
	}
}
