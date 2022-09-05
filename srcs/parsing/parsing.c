#include "../../includes/minishell.h"

int	ft_csch(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int error(t_shell *s, int i)
{
	if (i == 1)
	{
		s->error = 1;
		ft_putstr_fd("MALLOC ERROR\n", 2);
	}
	if (i == 1)
	{
		s->error = 1;
		ft_putstr_fd("COULD NOT OPEN FILE\n", 2);
	}
	return (-1);
}

int	init_par(t_shell *s)
{
	t_parsing	*par;

	par = malloc(sizeof(t_parsing));
	if (!par)
		return (error(s, 1));
	s->parsing = par;
	par->s = s;
	par->arg = NULL;
	par->com = NULL;
	par->l = s->lexer;
	par->std_in = dup(STDIN_FILENO);
	par->std_out = dup(STDOUT_FILENO);
	par->prev_in = STDIN_FILENO;
	par->block[0] = 0;
	par->block[1] = 1;
	make_block(s);
	return (0);
}

int	parsing(t_shell *s)
{
	if (!s->lexer || s->error == 1 || s->lexer->koi == END)
		return (-1);
	if (!s->error)
		init_par(s);
	return (0);
}

static int	redir_d(t_parsing *p, int type)
{
	int	flags;

	if (type == R_REDIR)
		flags = O_CREAT | O_TRUNC | O_WRONLY;
	else
		flags = O_CREAT | O_APPEND | O_WRONLY;
	p->block[1] = open(p->l->str, flags, 00644);
	if (p->block[1] == -1)
		return (error(p->s, 2));
	else
	{
		dup2(p->block[1], STDOUT_FILENO);
		close(p->block[1]);
		return (STDOUT_FILENO);
	}
}

static int    redir_g(t_parsing *p)
{
	//write(2, "ica\n", 4);
	p->block[0] = open(p->l->str, O_RDONLY);
	//write(2, "icb\n", 4);
	if (p->block[0] == -1)
		return (-1);
	else
	{
		dup2(p->block[0], STDIN_FILENO);
		close(p->block[0]);
	}
	return (STDIN_FILENO);
}

t_lexer	*redir(t_parsing *p)
{
	//write(2, "ict\n", 4);
	if (p->l->koi == R_REDIR || p->l->koi == RR_REDIR)
	{
		p->l = p->l->next;
		redir_d(p, p->l->prev->koi);
	}
	else if (p->l->koi == L_REDIR)
	{
		p->l = p->l->next;
		//write(2, "ict\n", 4);
		redir_g(p);
	}
	p->l = p->l->next;
	return (p->l);
}

// t_parsing	*pipe(t_parsing *par)
// {

// }
