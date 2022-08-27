#include "../../includes/minishell.h"

void	prompt(t_shell *s)
{
	char	*tmp;

	tmp = readline("minishell ➡️ ");
	s->prompt = tmp;
	if (*tmp == '\0')
		return ;
	add_history(tmp);
}
