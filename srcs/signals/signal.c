#include "../includes/minishell.h"


void	parent_signal(int sig)
{
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("\b\b  \b\b", 2);
	}
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		s()->sig->ret = 130;
	}
}

void	child_signal(int sig)
{
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit: (core dumped)\n", 2);
		s()->sig->ret = 131;
		s()->sig->sigint = 1;
	}
	else if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 2);
		s()->sig->ret = 130;
		s()->sig->sigint = 1;
	}
}

void	get_signal(int sig)
{
	if (s()->sig->pid)
		child_signal(sig);
	else
		parent_signal(sig);
}
