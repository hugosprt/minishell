#include "../../includes/minishell.h"

int	is_empty(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

void	skip_white_space(t_shell *s)
{
	while (*s->prompt && is_empty(*s->prompt))
		s->prompt++;
}

void	add_token_pip(t_shell *s)
{
	add_token_back(&s->lexer, PIPE, NOT_YET);
	s->prompt++;
}

void	add_token_rr(t_shell *s)
{
	if (s->prompt[1] == '>')
	{
		add_token_back(&s->lexer, RR_REDIR, NOT_YET);
		s->prompt += 2;
	}
	else
	{
		add_token_back(&s->lexer, R_REDIR, NOT_YET);
		s->prompt += 1;
	}
}

void	add_token_lr(t_shell *s)
{
	s->prompt += 1;

	if (s->prompt[0] == '<')
	{
		add_token_back(&s->lexer, LL_REDIR, NOT_YET);
		s->prompt += 2;
	}
	else
	{
		add_token_back(&s->lexer, L_REDIR, NOT_YET);
	}
}

int	is_separator(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

char	*ft_strldup(const char *source, int size)
{
	char	*dest;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(source);
	dest = (char *) malloc(1 + len * sizeof(char));
	if (dest == NULL)
		return (NULL);
	while (i < len && i != size)
	{
		dest[i] = source[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void skip_double_quote(t_shell *s, int *i)
{
	(*i)++;
	s->prompt++;
	while (*s->prompt && *s->prompt != '\"')
	{
		(*i)++;
		s->prompt++;
	}
	if (*s->prompt)
	{
		(*i)++;
		s->prompt++;
	}
}


void skip_single_quote(t_shell *s, int *i)
{
	(*i)++;
	s->prompt++;
	while (*s->prompt && *s->prompt != '\'')
	{
		(*i)++;
		s->prompt++;
	}
	if (*s->prompt)
	{
		(*i)++;
		s->prompt++;
	}
}

void	add_token_arg(t_shell *s)
{
	int 	i;
	char 	*tmp;

	tmp = s->prompt;
	i = 0;
	add_token_back(&s->lexer, ARG, NOT_YET);
	while (*s->prompt && !is_separator(*s->prompt))
	{
		if (*s->prompt == '\'')
			skip_single_quote(s, &i);
		if (*s->prompt == '\"')
			skip_single_quote(s, &i);
		i++;
		s->prompt++;
	}
	find_last_elem2(s->lexer)->str = ft_strldup(tmp, i);
}

