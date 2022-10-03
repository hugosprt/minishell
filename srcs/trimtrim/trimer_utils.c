/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trimer_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpol <rpol@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:45:24 by rpol              #+#    #+#             */
/*   Updated: 2022/10/03 13:45:27 by rpol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	supp_d_quote(t_lexer *l, t_quote quote, int *i, t_List st)
{
	int		fin;
	char	*start;
	char	*finish;
	char	*tmp1;
	char	*tmp2;

	fin = (*i) + 1;
	while (l->str[fin] && l->str[fin] != (char) quote)
	{
		if (l->str[fin] == '$' && l->quote == D_QUOTES)
			supp_dollarz(l, &fin, st);
		else
			fin++;
	}
	if (l->str == 0)
			fin--;
	tmp1 = ft_strldup(l->str, (*i));
	tmp2 = ft_strldup(l->str + (*i) + 1, fin - (*i) - 1);
	start = joinfree2(tmp1, tmp2);
	tmp1 = ft_strdup(l->str + fin + 1);
	finish = ft_strjoin(start, tmp1);
	free(l->str);
	l->str = finish;
	(*i) = fin - 1;
	return (free(start), free(tmp1), free(tmp2));
}

void	trimer_large(t_lexer *l, t_List st)
{
	int	i;

	i = 0;
	while (l->str[i])
	{
		if (l->str[i] == '\'')
			supp_d_quote(l, S_QUOTES, &i, st);
		else if (l->str[i] == '\"')
			supp_d_quote(l, D_QUOTES, &i, st);
		else if (l->str[i] == '$' && l->str[i + 1] != '$')
			supp_dollarz(l, &i, st);
		else
			i++;
	}
}

void	trimer(t_shell *shell, t_List st)
{
	t_lexer	*lexer;

	s()->lexer = shell->lexer;
	lexer = s()->lexer;
	if (lexer == NULL)
		return ;
	while (lexer)
	{
		if (lexer->koi == ARG && !shell->error)
			trimer_large(lexer, st);
		lexer = lexer->next;
	}
}
