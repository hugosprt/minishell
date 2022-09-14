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

void	return_value(t_lexer *l, char *start, int *i)
{
	char	*ret;

	ret = ft_itoa(s()->sig->ret);
	free(start);
	free(l->str);
	l->str = ret;
	(*i) += ft_strlen(ret);
}

void	not_expand(t_lexer *l, char *finish, char *start, char *ret, int fin)
{
	char		*tmp1;
	char		*tmp2;

	tmp2 = ft_strdup(l->str + fin);
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
	int		fin;
	char	*ret;
	char	*start;
	char	*finish;
	char	*var;

	fin = (*i) + 1;
	start = ft_strldup(l->str, (*i));
	finish = NULL;
	if (l->str[fin] == '?' && fin++)
		return (return_value(l, start, i));
	else
	{
		while ((ft_isalnum(l->str[fin]) || (l->str[fin] == '_')) && l->str[fin])
			fin++;
		var = ft_strldup(l->str + (*i) + 1,
				fin - (*i) - 1);
		ret = is_in_env2(st, var);
		if (ret == NULL)
			return (free(var), not_expand(l, finish, start, " ", fin));
	}
	not_expand(l, finish, start, ret, fin);
	free(var);
	(*i) += ft_strlen(ret);
}
