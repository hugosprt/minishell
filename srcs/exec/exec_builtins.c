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

void	exec(t_shell *s)
{
	char		**arg;
	char		*tmp;
	int			pid;
	t_parsing	*p;

	//write(2, "ic1\n", 4);
	p = s->parsing;
	//write(2, "ic2\n", 4);
	tmp = ft_strdup(p->arg);
	//write(2, "ic3\n", 4);
	s->parsing->com = cut_firste(s->parsing);
	//write(2, "ic4\n", 4);
	// ft_putstr_fd(s->parsing->com, 2);
	// write(2, "____", 4);
	// ft_putstr_fd(s->parsing->arg, 2);
	// write(2, "___\n", 4);
	if (!strcmp(s->parsing->com, "echo"))
	{
		//write(2, "ic5\n", 4);
		echo(s);
	}
	else if (!strcmp(p->com, "env"))
		print_env(p->s->st);
	else if (!strcmp(p->com, "export"))
	{
		arg = ft_split(p->arg, ' ');
		ft_export(p->s->st, arg);
	}	
	else if (!strcmp(p->com, "unset"))
	{
		arg = ft_split(p->arg, ' ');
		ft_unset(p->s->st, arg);
	}
	else if (!strcmp(p->com, "pwd"))
		pwd();
	else if (!strcmp(p->com, "cd"))
		cd(p->s->st, p->arg);
	else if (!strcmp(p->com, "exit"))
		ft_exit(p->arg);
	else
	{
		pid = fork();
		if (pid == 0)
		{
			if (!p->com)
				exit(1);
			execve(ispath(p->com), ft_split(tmp, ' '), s->str_env);
			write(2, "bash: ", 6);
			write(2, p->com, ft_strlen(p->com));
			write(2, ": command not found\n", 20);
			exit(2);
		}
		else
			waitpid(pid, NULL, 0);
	}
	if (p->arg)
	{
		p->arg = NULL;
		p->com = NULL;
	}

	//write(2, "ic3\n", 4);
}
