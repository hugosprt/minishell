/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpol <rpol@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:44:34 by rpol              #+#    #+#             */
/*   Updated: 2022/10/09 01:32:52 by rpol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	kayak(void)
{
	write(2, "\n", 1);
	s()->sig->ret = 130;
	s()->error = 3;
}

void	error_return(t_parsing *p, int i)
{
	if (i == 1)
	{
		if (ft_strrchr(p->error, '/'))
			write(2, "minishell: no such file or directory: ", 38);
		else
			write(2, "minishell: command not found: ", 30);
		write(2, p->error, ft_strlen(p->error));
		write(2, "\n", 1);
		exit (127);
	}
	else if (i == 2)
	{
		if (WIFEXITED(p->status))
			s()->sig->ret = WEXITSTATUS(p->status);
		if (WIFSIGNALED(p->status) && WCOREDUMP(p->status))
		{
			ft_putstr_fd("Quit (core dumped)\n", 2);
			s()->sig->ret = 131;
		}
		else
		{
			if (p->status == 567)
				kayak();
		}
	}
}

static void	make_the_split(t_shell *sh)
{
	sh->parsing->arg = ft_split(sh->parsing->com, '*');
	free(sh->parsing->com);
	sh->parsing->com = NULL;
}

void	make_the_fd_great_again(t_shell *sh)
{
	sh->parsing->std_in = dup(STDIN_FILENO);
	sh->parsing->std_out = dup(STDOUT_FILENO);
	dup2(sh->parsing->prev_in, STDIN_FILENO);
	if (sh->parsing->prev_in != 0)
		close(sh->parsing->prev_in);
	if (sh->parsing->nb_pipe <= 1)
		return ;
	sh->parsing->nb_pipe--;
	pipe(sh->parsing->pipe);
	dup2_close(sh->parsing->pipe[1], 1);
	sh->parsing->prev_in = dup(sh->parsing->pipe[0]);
	close(sh->parsing->pipe[0]);
}

int	make_block(t_shell *sh, t_parsing *p)
{
	make_the_fd_great_again(sh);
	while (p->l->koi != END && p->l->koi != PIPE)
	{
		if (p->l->koi == ARG)
		{
			p->com = joinfree1(p->com, p->l->str);
			p->l = p->l->next;
		}
		if (p->l->koi == R_REDIR || p->l->koi == RR_REDIR
			|| p->l->koi == L_REDIR || p->l->koi == LL_REDIR)
			p->l = redir(p);
	}
	make_the_split(sh);
	exec(sh, sh->parsing);
	dup2_close(sh->parsing->std_in, STDIN_FILENO);
	dup2_close(sh->parsing->std_out, STDOUT_FILENO);
	if (p->l->koi == PIPE && sh->error != 3)
	{
		sh->error = 0;
		sh->parsing->l = p->l->next;
		make_block(sh, p);
	}
	return (0);
}
