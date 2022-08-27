#include "../../includes/minishell.h"
       #include <sys/wait.h>
void	exec(t_shell *s, t_List st)
{
	char **arg;
	// char *cmd;
	if (!s->parsing)
		return ;
	else if (!strcmp(s->parsing->com, "echo"))
		echo(s);
	else if (!strcmp(s->parsing->com, "env"))
		print_env(st, s);
	else if (!strcmp(s->parsing->com, "export"))
	{
		
			arg = ft_split(s->parsing->arg, ' ');
			ft_export(st, arg);
		
	}	
	else if (!strcmp(s->parsing->com, "unset"))
	{
		arg = ft_split(s->parsing->arg, ' ');
		ft_unset(st, arg);
	}
	else if (!strcmp(s->parsing->com, "pwd"))
		pwd(s->parsing);
	else if (!strcmp(s->parsing->com, "cd"))
		cd(st, s->parsing->arg);
	// else
	// {
	// 	cmd =ft_strjoin("/bin/", s->parsing->com);
	// 	arg = ft_split(ft_strjoin(s->parsing->com, ft_strjoin(" ", s->parsing->arg)), ' ');
	// 	s->pid = fork();
	// 	//close(s->parsing->fd_out);
	// 	printf("%s\n", arg[0]);
	// 	if (s->pid == 0)
	// 		execve(cmd, arg, s->str_env);
	// 	int stat = 0;
	// 	wait(&stat);
	
	// }
}
