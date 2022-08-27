#include "../../includes/minishell.h"

void	pwd(t_parsing *par)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ft_putstr_fd(cwd, par->fd_out);
		ft_putstr_fd("\n", par->fd_out);
		if (par->fd_out != 1)
			close(par->fd_out);
	}
}
