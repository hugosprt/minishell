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

	(void) ac;
	(void) av;
	shell = s();
	if (!shell)
		return (0);
	if (!add_list(env, shell->env))
		return (0);
	minishell(shell);
}