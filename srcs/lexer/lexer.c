#include "../../includes/minishell.h"



void	add_token(t_shell *s)
{
	if (s->prompt == '|')
		add_token_pip(s);
	else if (s->prompt == '<')
		add_token_rr(s);
	else if (s->prompt == '>')
		add_token_lr(s);
	else
		add_token_arg(s);
	
}

int	lexer(t_shell *s)
{
	const char *tmp = s->prompt;

	if (s->prompt == NULL)
		return (1);
	while (*s->prompt != '\0' && !s->error)
	{
		if (is_empty(s->prompt))
			skip_white_space(s);
		else
			add_token(s->prompt);
	}
	return (1);
}