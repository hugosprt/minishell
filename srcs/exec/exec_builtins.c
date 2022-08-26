#include "../../includes/minishell.h"

void	exec(t_shell *s)
{
	if (strcmp(s->parsing->com, "echo"))
		echo(s);
}