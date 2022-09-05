#include "../../includes/minishell.h"

static int	last_exec(t_shell *s)
{
	if (s->parsing->block[0] == 0)
	{
		dup2(s->parsing->prev_in, STDIN_FILENO);
		if (s->parsing->prev_in != 0)
			close(s->parsing->prev_in);
	}
	// ft_putstr_fd("last exec", 2);
	// write(2, "___\n", 4);
	exec(s);
	dup2(s->parsing->std_in, STDIN_FILENO);
	dup2(s->parsing->std_out, STDOUT_FILENO);
	close(s->parsing->std_out);
	return (0);
}

static t_lexer	*mario(t_shell *s)
{
	//write(2, "ici\n", 4);
	if (s->parsing->block[0] == 0)
	{
		dup2(s->parsing->prev_in, STDIN_FILENO);
		if (s->parsing->prev_in != 0)
			close(s->parsing->prev_in);
	}
	if (s->parsing->block[1] == 1)
	{
		pipe(s->parsing->pipe);
		dup2(s->parsing->pipe[STDOUT_FILENO], STDOUT_FILENO);
		close(s->parsing->pipe[STDOUT_FILENO]);
		s->parsing->prev_in = dup(s->parsing->pipe[STDIN_FILENO]);
		close(s->parsing->pipe[STDIN_FILENO]);
	}
	exec(s);
	dup2(s->parsing->std_in, STDIN_FILENO);
	close(s->parsing->std_in);
	dup2(s->parsing->std_out, STDOUT_FILENO);
	close(s->parsing->std_out);
//	write(2, "ic2\n", 4);
	s->parsing->l = s->parsing->l->next;
	return (s->parsing->l);
}

int	make_block(t_shell *s)
{
	t_parsing	*p;

	p = s->parsing;
	if (p->l->koi == ARG)
	{
		if (p->arg)
			p->arg = n_strjoin(3, p->arg, " ", p->l->str);
		else
			p->arg = p->l->str;
		p->l = p->l->next;
	}
	//write(2, "icw\n", 4);
	if (p->l->koi == R_REDIR || p->l->koi == RR_REDIR || p->l->koi == L_REDIR)
		p->l = redir(p);
	s->parsing = p;
	if (p->l->koi == PIPE)
		p->l = mario(s);
	if (p->l->koi == END)
	{
		last_exec(s);
		s->parsing->l->koi = 10;
		return (0);
	}
	if (p->l->koi != 10)
		make_block(s);
	return (0);
}
