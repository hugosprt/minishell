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


char	*add_cmd(char **cmd_paths, char *args, t_parsing *com)
{
	char	*guess;
	char	*tmp;

	(void) com;
	if (access(args, 0) == 0)
		return (args);
	while (*cmd_paths)
	{
		tmp = ft_strjoin(*cmd_paths, "/");
		guess = ft_strjoin(tmp, args);
		free(tmp);
		if (access(guess, 0) == 0)
			return (guess);
		free(guess);
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
	char		*path;
	char		**cmd_path;
	int			i;

	i = 0;
	// write(2, "ic1\n", 4);
	p = sh->parsing;
	t = p->arg;
	// printtab(t);
	// write(2, "ic2\n", 4);
	// write(2, "ic5\n", 4);
	//write(2, "ic3\n", 4);
	p->com = p->arg[0];
	(void) t;
	//write(2, "ic4\n", 4);
	// ft_putstr_fd(sh->parsing->com, 2);
	// write(2, "____", 4);
	// ft_putstr_fd(sh->parsing->arg, 2);
	// write(2, "___\n", 4);

	if (!strcmp(p->com, "echo"))
	{
		echo(sh);
	}
	else if (!strcmp(p->com, "env"))
		print_env(sh, sh->st);
	else if (!strcmp(p->com, "export"))
	{
		ft_export(sh->st, t);
	}	
	else if (!strcmp(p->com, "unset"))
	{
		ft_unset(sh->st, t++);
	}
	else if (!strcmp(p->com, "pwd"))
		pwd();
	else if (!strcmp(p->com, "cd"))
		cd(sh->st, p->arg[1]);
	else if (!strcmp(p->com, "exit"))
		ft_exit(t++);
	else
	{
		
		
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
				if (ft_strrchr(p->error,'/'))
					write(2, "minishell: no such file or directory: ", 38);
				else
					write(2, "minishell: command not found: ", 30);
				write(2, p->error, ft_strlen(p->error));
				write(2, "\n", 1);
				exit (127);
			}
			execve(p->com, t, sh->str_env);
			
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
