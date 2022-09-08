#include "../../includes/minishell.h"

void	pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ft_putstr_fd(cwd, 1);
		ft_putstr_fd("\n", 1);
	}
	else
	{
		ft_putstr_fd("minishell: pwd: ", 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		s()->sig->ret = 1;
	}
}
