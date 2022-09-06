#include "../../includes/minishell.h"
#include <sys/wait.h>

// static char	*cut_firste(t_parsing *p)
// {
// 	int		i;
// 	char	*str;

// 	i = 0;
// 	str = p->arg;

// 	if (p->com)
// 		free(p->com);
// 	while (str[i] == ' ')
// 		i++;
// 	while (str[i])
// 	{
// 		if (str[i] == ' ')
// 		{
// 			p->com = ft_strncpy(str, i);
// 			i++;
// 			p->arg = str + i;
// 			return (p->com);
// 		}
// 		i++;
// 	}
// 	p->com = p->arg;
// 	p->arg = NULL;
// 	return (p->com);
// }

static char	*ispath(char *com)
{
	if(com[0] == '/')
		return (com);
	else
		return (ft_strjoin("/bin/", com));
}

// static void	printtab(char **t)
// {
// 	int	i;

// 	i = 0;
// 	while (t[i])
// 	{
// 		ft_putstr_fd(t[i], 2);
// 		write(2, "\n", 1);
// 		i++;
// 	}
// }

void	exec(t_shell *sh)
{
	int			pid;
	char		**t;
	t_parsing	*p;

	// write(2, "ic1\n", 4);
	p = sh->parsing;
	t = p->arg;
	// printtab(t);
	// write(2, "ic2\n", 4);
	// write(2, "ic5\n", 4);
	//write(2, "ic3\n", 4);
	sh->parsing->com = p->arg[0];
	//write(2, "ic4\n", 4);
	// ft_putstr_fd(sh->parsing->com, 2);
	// write(2, "____", 4);
	// ft_putstr_fd(sh->parsing->arg, 2);
	// write(2, "___\n", 4);
	if (!strcmp(sh->parsing->com, "echo"))
	{
		echo(sh);
	}
	else if (!strcmp(p->com, "env"))
		print_env(sh->st);
	else if (!strcmp(p->com, "export"))
	{
		ft_export(sh->st, t);
	}	
	else if (!strcmp(p->com, "unset"))
	{
		ft_unset(sh->st, t);
	}
	else if (!strcmp(p->com, "pwd"))
		pwd();
	else if (!strcmp(p->com, "cd"))
		cd(sh->st, p->arg[1]);
	else if (!strcmp(p->com, "exit"))
		ft_exit(p->arg[1]);
	else
	{
		pid = fork();
		if (pid == 0)
		{
			if (!p->com)
				exit(1);
			execve(ispath(p->com), t, sh->str_env);
			write(2, "bash: ", 6);
			write(2, p->com, ft_strlen(p->com));
			write(2, ": command not found\n", 20);
			exit(127);
		}
		waitpid(pid, &p->status, 0);
		if (WIFEXITED(p->status))
		{
			s()->sig->ret = WEXITSTATUS(p->status);
		}
		else
			s()->sig->ret = 0;

	}
	if (p->arg)
	{
		p->arg = NULL;
		p->com = NULL;
	}

	//write(2, "ic3\n", 4);
}
