#include "../../includes/minishell.h"

int	error(t_shell *sh, int i)
{
	if (i == 1)
	{
		sh->error = 1;
		ft_putstr_fd("MALLOC ERROR\n", 2);
	}
	if (i == 1)
	{
		sh->error = 1;
		ft_putstr_fd("COULD NOT OPEN FILE\n", 2);
	}
	return (-1);
}

int	count_pipe(t_lexer *lex)
{
	t_lexer	*l;
	int		i;

	l = lex;
	i = 0;
	while (l->koi != END)
	{
		if (l->koi == PIPE)
			i++;
		l = l->next;
	}
	return (i);
}

int	init_par(t_shell *sh)
{
	t_parsing	*par;

	par = malloc(sizeof(t_parsing));
	if (!par)
		return (error(sh, 1));
	sh->parsing = par;
	par->sh = sh;
	par->arg = NULL;
	par->com = NULL;
	par->l = sh->lexer;
	par->prev_in = STDIN_FILENO;
	par->nb_pipe = count_pipe(sh->lexer);
	make_block(sh);
	return (0);
}

int	parsing(t_shell *sh)
{
	if (!sh->lexer || sh->error == 1 || sh->lexer->koi == END)
		return (-1);
	if (!sh->error)
		init_par(sh);
	return (0);
}

static int	redir_d(t_parsing *p, int type)
{
	int	flags;
	int	fd;

	if (type == R_REDIR)
		flags = O_CREAT | O_TRUNC | O_WRONLY;
	else
		flags = O_CREAT | O_APPEND | O_WRONLY;
	fd = open(p->l->str, flags, 00644);
	if (fd == -1)
		return (error(p->sh, 2));
	else
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
		return (STDOUT_FILENO);
	}
}

static int    redir_g(t_parsing *p)
{
	int	fd;

	fd = open(p->l->str, O_RDONLY);
	if (fd == -1)
		return (-1);
	else
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	return (STDIN_FILENO);
}

t_lexer	*redir(t_parsing *p)
{
	if (p->l->koi == R_REDIR || p->l->koi == RR_REDIR)
	{
		p->l = p->l->next;
		redir_d(p, p->l->prev->koi);
	}
	else if (p->l->koi == L_REDIR)
	{
		p->l = p->l->next;
		redir_g(p);
	}
	p->l = p->l->next;
	return (p->l);
}
