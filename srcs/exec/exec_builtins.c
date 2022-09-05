#include "../../includes/minishell.h"
#include <sys/wait.h>

static char	*cut_firste(t_parsing *p)
{
	int		i;
	char	*str;

	i = 0;
	str = p->arg;

	if (p->com)
		free(p->com);
	while (str[i] == ' ')
		i++;
	while (str[i])
	{
		if (str[i] == ' ')
		{
			p->com = ft_strncpy(str, i);
			i++;
			p->arg = str + i;
			return (p->com);
		}
		i++;
	}
	p->com = p->arg;
	p->arg = NULL;
	return (p->com);
}

static char	*ispath(char *com)
{
	if(com[0] == '/')
		return (com);
	else
		return (ft_strjoin("/bin/", com));
}

void	exec(t_shell *sh)
{
	char		**arg;
	char		*tmp;
	int			pid;
	t_parsing	*p;

	//write(2, "ic1\n", 4);
	p = sh->parsing;
	//write(2, "ic2\n", 4);
	tmp = ft_strdup(p->arg);
	//write(2, "ic3\n", 4);
	sh->parsing->com = cut_firste(sh->parsing);
	//write(2, "ic4\n", 4);
	// ft_putstr_fd(sh->parsing->com, 2);
	// write(2, "____", 4);
	// ft_putstr_fd(sh->parsing->arg, 2);
	// write(2, "___\n", 4);
	if (!strcmp(sh->parsing->com, "echo"))
	{
		//write(2, "ic5\n", 4);
		echo(sh);
	}
	else if (!strcmp(p->com, "env"))
		print_env(sh->st);
	else if (!strcmp(p->com, "export"))
	{
		arg = ft_split(p->arg, ' ');
		ft_export(sh->st, arg);
	}	
	else if (!strcmp(p->com, "unset"))
	{
		arg = ft_split(p->arg, ' ');
		ft_unset(sh->st, arg);
	}
	else if (!strcmp(p->com, "pwd"))
		pwd();
	else if (!strcmp(p->com, "cd"))
		cd(sh->st, p->arg);
	else if (!strcmp(p->com, "exit"))
		ft_exit(p->arg);
	else
	{
		pid = fork();
		if (pid == 0)
		{
			if (!p->com)
				exit(1);
			execve(ispath(p->com), ft_split(tmp, ' '), sh->str_env);
			write(2, "bash: ", 6);
			write(2, p->com, ft_strlen(p->com));
			write(2, ": command not found\n", 20);
			exit(127);
		}
		waitpid(pid, &p->status, 0);
		if (WIFEXITED(p->status))
			s()->sig->ret = WEXITSTATUS(p->status);
	}
	if (p->arg)
	{
		p->arg = NULL;
		p->com = NULL;
	}

	//write(2, "ic3\n", 4);
}
