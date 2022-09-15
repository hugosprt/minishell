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

	if (st == NULL)
		return (0);
	while (st != NULL)
	{
		if (!ft_strcmp_2(var_name, st->var))
		{
			ret = st->value;
			return (ret);
		}
		st = st->next;
	}
	return (NULL);
}

void	not_expand(t_lexer *l, char *finish, char *start, char *ret)
{
	char		*tmp1;
	char		*tmp2;

	tmp2 = ft_strdup(l->str + s()->fin);
	tmp1 = ft_strjoin(ret, tmp2);
	finish = ft_strjoin(start, tmp1);
	free(l->str);
	l->str = finish;
	free(start);
	free(tmp1);
	free(tmp2);
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
			return (free(var), not_expand(l, finish, start, " "));
		free(var);
	}
	not_expand(l, finish, start, ret);
	(*i) += ft_strlen(ret);
	free(ret);
}
