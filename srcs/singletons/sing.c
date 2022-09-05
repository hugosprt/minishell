#include "../../includes/minishell.h"

t_shell	*s(void)
{
	static t_shell	*s;

	if (!s)
	{
		s = malloc(sizeof(t_shell));
		s->env = malloc(sizeof(t_shell));
		s->lexer = malloc(sizeof(t_shell));
		s->sig = malloc(sizeof(t_shell));
		s->sig->ret = 0;
	}
	return (s);
}
