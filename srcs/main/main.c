#include "../../includes/minishell.h"

void	minishell(t_shell *s)
{
	while (1)
	{
		prompt(s);
	}
}

int main(int ac, char **av, char **env)
{
	t_shell *shell;
	t_List	st;

	(void) ac;
	(void) av;
	st = NULL;
	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (0);
	if (!add_list(env, st))
		return (0);
	minishell(shell);
}