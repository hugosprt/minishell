#include "../../includes/minishell.h"

char	*add_cmd(char **cmd_paths, char *args, t_parsing *com)
{
	char	*ret;
	char	*tmp;

	if (access(args, X_OK) == 0)
		return (args);
	while (*cmd_paths)
	{
		tmp = ft_strjoin(*cmd_paths, "/");
		ret = ft_strjoin(tmp, args);
		free(tmp);
		if (access(ret, X_OK) == 0)
			return (ret);
		free(ret);
		cmd_paths++;
	}
	com->error = ft_strdup(args);
	return (NULL);
}

char	*get_path(t_shell *shell)
{
	t_ListElement	*tmp;

	tmp = NULL;
	tmp = (shell->st);
	while (tmp)
	{
		if (0 == ft_strcmp_2(tmp->var, "PATH"))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

void	le_exec(t_shell *sh, t_parsing *p, int pid)
{
	pid = fork();
	if (pid == 0)
	{
		if (!ft_strlen(p->arg[0]) == 0)
			make_path(sh, p);
		else
		{
			p->error = " ";
			p->com = NULL;
		}
		if (!p->com)
		{
			error_return(p, 1);
		}
		execve(p->com, p->arg, sh->str_env);
		exit (0);
	}
	p->status = 567;
	waitpid(pid, &p->status, 0);
	error_return(p, 2);
}

void	exec(t_shell *sh, t_parsing *p)
{
	if (!p->arg)
		return ;
	if (sh->error)
		return (free_stuff(p));
	if (!ft_strcmp(p->arg[0], "echo"))
		echo(sh, 1, 1);
	else if (!ft_strcmp(p->arg[0], "env"))
		print_env(sh, sh->st);
	else if (!ft_strcmp(p->arg[0], "export"))
		ft_export(sh->st, p->arg);
	else if (!ft_strcmp(p->arg[0], "unset"))
		ft_unset(sh->st, p->arg);
	else if (!ft_strcmp(p->arg[0], "pwd"))
		pwd();
	else if (!ft_strcmp(p->arg[0], "cd"))
		cd(sh->st, p->arg[1]);
	else if (!ft_strcmp(p->arg[0], "exit"))
	{
		if (!p->nb_pipe)
			ft_exit(p->arg);
	}
	else
		le_exec(sh, p, 0);
	free_stuff(p);
}
