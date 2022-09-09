#include "../../includes/minishell.h"

char	*add_cmd(char **cmd_paths, char *args, t_parsing *com)
{
	char	*ret;
	char	*tmp;

	if (access(args,  X_OK) == 0)
		return (args);
	while (*cmd_paths)
	{
		tmp = ft_strjoin(*cmd_paths, "/");
		ret = ft_strjoin(tmp, args);
		free(tmp);
		if (access(ret,  X_OK) == 0)
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

void	le_exec(t_shell *sh, t_parsing *p, int i, int pid)
{
	char	*path;
	char		**cmd_path;

	pid = fork();
	if (pid == 0)
	{
		path = get_path(sh);
		if (!path)
			path_not_set(p);
		cmd_path = ft_split(path, ':');
		p->com = add_cmd(cmd_path, p->com, p);
		while (cmd_path[i])
			free(cmd_path[i++]);
		if (!p->com)
		{
			if (ft_strrchr(p->error, '/'))
				write(2, "minishell: no such file or directory: ", 38);
			else
				write(2, "minishell: command not found: ", 30);
			write(2, p->error, ft_strlen(p->error));
			write(2, "\n", 1);
			exit (127);
		}
		execve(p->com, p->arg, sh->str_env);
		exit (0);
	}
	waitpid(pid, &p->status, 0);
	if (WIFEXITED(p->status))
	{
		s()->sig->ret = WEXITSTATUS(p->status);
	}
	else
		s()->sig->ret = 0;
}

void	exec(t_shell *sh, t_parsing *p)
{
	if (!p->arg)
		return ;
	p->com = p->arg[0];
	if (!strcmp(p->com, "echo"))
		echo(sh, 1, 1);
	else if (!strcmp(p->com, "env"))
		print_env(sh, sh->st);
	else if (!strcmp(p->com, "export"))
		ft_export(sh->st, p->arg);
	else if (!strcmp(p->com, "unset"))
		ft_unset(sh->st, p->arg);
	else if (!strcmp(p->com, "pwd"))
		pwd();
	else if (!strcmp(p->com, "cd"))
		cd(sh->st, p->arg[1]);
	else if (!strcmp(p->com, "exit"))
	{
		if (!p->nb_pipe)
			ft_exit(p->arg);
	}
	else
		le_exec(sh, p, 0, 0);
	if (p->arg)
		free_stuff(p);
}
