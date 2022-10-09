/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tester.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hspriet <hspriet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:41:30 by rpol              #+#    #+#             */
/*   Updated: 2022/10/09 15:35:46 by hspriet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	size_list(t_lexer *s)
{
	t_lexer	*tmp;
	int		count;

	tmp = s;
	count = 0;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

int	first_arg(t_shell *s, t_lexer *l)
{
	t_lexer	*tmp;

	tmp = l;
	if (size_list(tmp) == 2)
		if (tmp->koi > 0)
			syntax_problem(s, 5);
	if (tmp->koi > 2 && tmp->next->koi > 2)
		syntax_problem(s, 3);
	else
	{
		tmp = tmp->next;
		while (tmp && tmp->next && !s->error)
		{
			if (find_last_elem(tmp) == PIPE)
			{
				syntax_problem(s, 0);
				break ;
			}
			test_pipe(s, tmp);
			tmp = tmp->next;
		}
	}
	return (1);
}

int	find_last_elem(t_lexer *l)
{
	t_lexer	*tmp;

	tmp = l;
	if (tmp == NULL)
		return (0);
	while (NULL != tmp)
	{
		if (END == tmp->next->koi)
			return (tmp->koi);
		tmp = tmp->next;
	}
	return (0);
}

t_lexer	*find_last_elem2(t_lexer *l)
{
	t_lexer	*tmp;

	tmp = l;
	if (tmp == NULL)
		return (NULL);
	while (NULL != tmp)
	{
		if (NULL == tmp->next)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

int	test_pipe(t_shell *s, t_lexer *l)
{
	t_lexer	*tmp;

	tmp = l;
	if (tmp->prev->koi == R_REDIR && tmp->koi == PIPE)
		syntax_problem(s, 0);
	else if (tmp->koi == L_REDIR && tmp->next->koi == END)
		syntax_problem(s, 5);
	else if (tmp->prev->koi == L_REDIR && tmp->koi == PIPE)
		syntax_problem(s, 0);
	else if (tmp->prev->koi == RR_REDIR && tmp->koi == L_REDIR)
		syntax_problem(s, 2);
	else if (tmp->prev->koi == PIPE && tmp->koi == PIPE
		&& tmp->next->koi == PIPE)
		syntax_problem(s, 0);
	else if (tmp->koi == LL_REDIR && tmp->next->koi >= END)
		syntax_problem(s, 5);
	else if (tmp->koi == R_REDIR && tmp->next->koi == END)
		syntax_problem(s, 5);
	else if (tmp->prev->koi == R_REDIR && tmp->koi == L_REDIR)
		syntax_problem(s, 5);
	else if (tmp->prev->koi == L_REDIR && tmp->koi == R_REDIR)
		syntax_problem(s, 5);
	else if (tmp->koi == RR_REDIR && tmp->next->koi >= END)
		syntax_problem(s, 5);
	return (1);
}
