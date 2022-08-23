#include "../../includes/minishell.h"



int		is_empty(char c)
{
	if  (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

void	skip_white_space(t_shell *s)
{
	while (*s->prompt && is_empty(*s->prompt))
		s->prompt++;
}