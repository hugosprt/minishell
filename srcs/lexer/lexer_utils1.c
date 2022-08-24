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
	add_token_back(&s->lexer, PIPE);
	s->prompt++;
}

void	add_token_rr(t_shell *s)
{
	if (s->prompt[1] == '>')
	{
		add_token_back(&s->lexer, RR_REDIR);
		s->prompt += 2;
	}
	else
	{
		add_token_back(&s->lexer, R_REDIR);
		s->prompt += 1;
	}
}

void	add_token_lr(t_shell *s)
{
	s->prompt += 1;

	if (s->prompt[0] == '<')
	{
		add_token_back(&s->lexer, LL_REDIR);
		s->prompt += 2;
	}
	else
	{
		add_token_back(&s->lexer, L_REDIR);
	}
}

int	is_separator(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

void	add_token_arg(t_shell *s)
{
	add_token_back(&s->lexer, ARG);
	while (*s->prompt && !is_separator(*s->prompt))
	{
		s->prompt++;
	}
}