#include "../../includes/minishell.h"

void	prompt(t_shell *s)
{
	char	*tmp;

	tmp = readline("minishell: ");
	s->prompt = tmp;
	if (s->prompt == NULL)
		ctrl_d_exit();
	if (*tmp == '\0')
		return ;
	add_history(tmp);
}
