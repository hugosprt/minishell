#include "../../includes/minishell.h"

void	ctrl_d_exit(void)
{
	uint32_t	exit_c;

	exit_c = s()->sig->ret;
	ft_putstr_fd("exit\n", 2);
	exit(exit_c);
}

void
	handle_int(siginfo_t *siginfo)
{
	// if (s()->prog_state == OUT_OF_SHELL)
	// {
	// 	__putchar('\n', 1);
	// 	exit(0);
	// }
	if (siginfo->si_pid != 0)
	{
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		s()->sig->ret = 130;
	}
	else
		wait(NULL);
}

void
	signal_handler(int signal, siginfo_t *siginfo, void *data)
{
	(void)data;
	if (signal == SIGINT)
		handle_int(siginfo);
}

void	signal_gestion(t_shell *s)
{
	struct sigaction	sa;

	(void)s;
	ft_memset(&sa, 0, sizeof(struct sigaction));
	sa.sa_sigaction = signal_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}