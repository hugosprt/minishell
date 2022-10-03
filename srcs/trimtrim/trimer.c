/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trimer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpol <rpol@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:45:34 by rpol              #+#    #+#             */
/*   Updated: 2022/10/03 13:45:36 by rpol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_quote(char c)
{
	if (c == '\'')
		return (1);
	if (c == '\"')
		return (1);
	return (0);
}

char	*is_in_env2(t_List st, char *var_name)
{
	char	*ret;
	t_List	tmp;

	tmp = st;
	if (tmp == NULL)
		return (0);
	while (tmp != NULL)
	{
		if (!ft_strcmp_2(var_name, tmp->var))
		{
			ret = tmp->value;
			return (ret);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void	not_expand(t_lexer *l, char *finish, char *start, char *ret)
{
	char		*tmp1;
	char		*tmp2;
	char		*tmp3;

	tmp2 = ft_strdup(l->str + s()->fin);
	tmp1 = ft_strjoin(ret, tmp2);
	finish = ft_strjoin(start, tmp1);
	free(l->str);
	l->str = finish;
	free(start);
	free(tmp1);
	free(tmp2);
	tmp3 = ft_itoa(s()->sig->ret);
	if (ft_strcmp_2(ret, tmp3))
		s()->b = 1;
	else
		s()->b = 0;
	free(tmp3);
}

void	ft_24line(char *ret)
{
	if (s()->b == 0)
		free(ret);
}

void	supp_dollarz(t_lexer *l, int *i, t_List st)
{
	char	*ret;
	char	*start;
	char	*finish;
	char	*var;

	s()->fin = (*i) + 1;
	start = ft_strldup(l->str, (*i));
	finish = NULL;
	if (l->str[s()->fin] == '?' && s()->fin++)
		ret = ft_itoa(s()->sig->ret);
	else
	{
		while ((ft_isalnum(l->str[s()->fin]) || (l->str[s()->fin] == '_'))
			&& l->str[s()->fin])
			s()->fin++;
		var = ft_strldup(l->str + (*i) + 1,
				s()->fin - (*i) - 1);
		ret = is_in_env2(st, var);
		if (ret == NULL)
			return (free(var), not_expand(l, finish, start, ""));
		free(var);
	}
	not_expand(l, finish, start, ret);
	(*i) += ft_strlen(ret);
	ft_24line(ret);
}
