#include "../../includes/minishell.h"

void	prompt(t_shell *s)
{
	char	*tmp;

	tmp = readline("minishell :");
	s->prompt = tmp;
	add_history(tmp);
}
