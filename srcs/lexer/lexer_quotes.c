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
		printf("quote pas fermees\n");
		return ;
	}
	(*str)++;
}

void	doubl_quote(t_shell *s, char **str, t_lexer *l)
{
	(void) s;
	if (l->quote == D_QUOTES || l->quote == D_QUOTES)
		l->quote = MIX_QUOTES;
	else
		l->quote = D_QUOTES;
	(*str)++;
	while (**str != '\"' && **str != '\0')
		(*str)++;
	if (!(**str))
	{	
		printf("quote pas fermees\n");
		return ;
	}
	(*str)++;
}

void	set_quote(t_shell *s, t_lexer *l)
{
	char *str;

	str =l->str;

	while (*str)
	{
		if (*str == '\'')
			sing_quote(s, &str, l);
		else if (*str == '\"')
			doubl_quote(s, &str, l);
		else 
			str++;
	}
}

void	index_quotes(t_shell *s)
{
	t_lexer *tmp;

	tmp = s->lexer;
	if (tmp == NULL)
		return ;
	while (tmp != NULL)
	{
		if (tmp->koi == ARG)
			set_quote(s, tmp);
		tmp = tmp->next;
	}
}