#include "../../includes/minishell.h"


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

int	make_block(t_shell *sh)
{
	t_parsing	*p;

	p = sh->parsing;
	make_the_fd_great_again(sh);
	while (p->l->koi != END && p->l->koi != PIPE)
	{
		if (p->l->koi == ARG)
		{
			p->arg = add2tab(p->arg, p->l->str);
			p->l = p->l->next;
		}
		if (p->l->koi == R_REDIR || p->l->koi == RR_REDIR 
					|| p->l->koi == L_REDIR || p->l->koi == LL_REDIR)
			p->l = redir(p);
	}
	exec(sh);
	dup2_close(sh->parsing->std_in, STDIN_FILENO);
	dup2_close(sh->parsing->std_out, STDOUT_FILENO);
	if (p->l->koi == PIPE)
	{
		sh->parsing->l = p->l->next;
		make_block(sh);
	}
	return (0);
}
