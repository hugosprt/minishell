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
	char *ret;

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


void	supp_dollarz(t_shell *shell, t_lexer *l, int *i , t_List st)
{
	int 	fin;
	char	*ret;
	char	*start;
	char	*finish;
	char 	*var;

	(void) shell;
	fin = (*i) + 1;
	start = ft_strldup(l->str, (*i));
	finish = NULL;
	if (l->str[fin] == '?' && fin++)
		ret = ft_itoa(s()->sig->ret);	else
	{
		while ((ft_isalnum(l->str[fin]) || (l->str[fin] == '_')) && l->str[fin])
		{
			fin++;
		}
		var = ft_strldup(l->str + (*i) + 1,
				fin - (*i) - 1);
		ret = is_in_env2(st, var);
		if (ret == NULL)
		{
			finish = ft_strjoin(start, ft_strjoin(" ",
				ft_strdup(l->str + fin)));
			l->str = finish;
			return ;
		}
	}
	finish = ft_strjoin(start, ft_strjoin(ret,
				ft_strdup(l->str + fin)));
	l->str = finish;
	(*i) += ft_strlen(ret);

}

void	supp_d_quote(t_shell *s, t_lexer *l, t_quote quote, int *i, t_List st)
{
	int		fin;
	char	*start;
	char	*finish;

	(void) s;
	(void) quote;
	fin = (*i) + 1;
	while (l->str[fin] && l->str[fin] != (char) quote)
	{
		if (l->str[fin] == '$' && l->quote == D_QUOTES)
			supp_dollarz(s, l, &fin, st);
		else
			fin++;
	}
	if (l->str == 0)
			fin--;
	start = ft_strjoin(ft_strldup(l->str, (*i)),
			ft_strldup(l->str + (*i) + 1, fin - (*i) - 1));
	finish = ft_strjoin(start, ft_strdup(l->str + fin + 1));
	l->str = finish;
	free(start);
	(*i) = fin - 1;
}

void	trimer_large(t_shell *s, t_lexer *l, t_List st)
{
	int	i;

	i = 0;
	while (l->str[i])
	{
		if (l->str[i] == '\'')
		{
			supp_d_quote(s, l, S_QUOTES, &i, st);
		}
		else if (l->str[i] == '\"')
		{
			supp_d_quote(s, l, D_QUOTES, &i, st);
		}
		else if (l->str[i] == '$')
			supp_dollarz(s, l, &i, st);
		else
			i++;
	}
}

void	trimer(t_shell *s, t_List st)
{
	t_lexer	*lexer;

	lexer = s->lexer;
	if (lexer == NULL)
		return ;
	while (lexer)
	{
		if (lexer->koi == ARG && !s->error)
			trimer_large(s, lexer, st);
		lexer = lexer->next;
	}
}
