#include "../../includes/minishell.h"

int is_quote(char c)
{
	if (c == '\'')
		return (1);
	if (c == '\"')
		return (1);
	return (0);
	
}


void	supp_d_quote(t_shell *s, t_lexer *l, t_quote quote, int *i)
{
	int	fin;
	char *start;
	char *finish;

	(void) s;
	(void) quote;
	fin = (*i) + 1;
	while (l->str[fin] && l->str[fin] != (char) quote)
	{
		fin++;
	}
	if (l->str == 0)
			fin--;
	start = ft_strjoin(ft_strldup(l->str, (*i)), ft_strldup(l->str + (*i) + 1 , fin - (*i) - 1));
	finish = ft_strjoin(start, ft_strdup(l->str + fin + 1));
	l->str = finish;
	free(start);
	(*i) = fin - 1;
}

void	trimer_large(t_shell *s, t_lexer *l)
{
	int	i;

	i = 0;
	while (l->str[i])
	{
		if (l->str[i] == '\'')
		{
			supp_d_quote(s, l, S_QUOTES, &i);
		}
		else if (l->str[i] =='\"')
		{
			supp_d_quote(s, l, D_QUOTES, &i);
		}
		else 
			i++;
	}
}

void	trimer(t_shell *s)
{
	t_lexer	*lexer;

	lexer = s->lexer;
	if (lexer == NULL)
		return ;
	while (lexer)
	{
		if (lexer->koi == ARG)
			trimer_large(s, lexer);
		lexer = lexer->next;
	}
	
}