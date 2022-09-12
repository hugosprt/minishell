#include "../../includes/minishell.h"

void	dup2_close(int fd, int old_fd)
{
	dup2(fd, old_fd);
	close(fd);
}

static void	redir_d(t_parsing *p, int type)
{
	int	flags;
	int	fd;

	if (type == R_REDIR)
		flags = O_CREAT | O_TRUNC | O_WRONLY;
	else
		flags = O_CREAT | O_APPEND | O_WRONLY;
	fd = open(p->l->str, flags, 00644);
	if (fd == -1)
		error(p->sh, 2);
	else
		dup2_close(fd, 1);
}

static void	redir_g(t_parsing *p)
{
	int	fd;

	fd = open(p->l->str, O_RDONLY);
	if (fd == -1)
		error(p->sh, 2);
	else
		dup2_close(fd, 0);
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
	else if (p->l->koi == LL_REDIR)
	{
		p->l = p->l->next;
		ici_fichier(p);
	}
	free(p->l->str);
	p->l = p->l->next;
	return (p->l);
}
