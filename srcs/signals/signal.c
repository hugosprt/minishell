/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpol <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:44:59 by rpol              #+#    #+#             */
/*   Updated: 2022/10/09 15:38:35 by rpol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ctrl_d_exit(void)
{
	ft_exit(0, NULL, 0);
}

void	handle_int(siginfo_t *siginfo)
{
	if (s()->t == 1)
	{
		exit(130);
	}
	if (siginfo->si_pid != 0)
	{
		ft_putchar_fd('\n', 2);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		s()->sig->ret = 130;
	}
	else
		wait(NULL);
}

void	signal_handler(int signal, siginfo_t *siginfo, void *data)
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
