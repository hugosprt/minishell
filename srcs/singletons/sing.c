#include "../../includes/minishell.h"


t_shell		*s()
{
	static t_shell *s;

	if (!s)
	{
		s = malloc(sizeof(t_shell));
		s->env = malloc(sizeof(t_shell));
		s->lexer = malloc(sizeof(t_shell));
	}
	return (s);
}