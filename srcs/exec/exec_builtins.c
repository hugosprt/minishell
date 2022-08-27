#include "../../includes/minishell.h"

void	exec(t_shell *s, t_List st)
{
	if (!s->parsing)
		return ;
	else if (!strcmp(s->parsing->com, "echo"))
		echo(s);
	else if (!strcmp(s->parsing->com, "env"))
		print_env(st);
//	else if (!strcmp(s->parsing->com, "export"))
//		export(st, s);
//	else if (!strcmp(s->parsing->com, "unset"))
//		unset(st, s);
	else if (!strcmp(s->parsing->com, "pwd"))
		pwd(s->parsing);
}
