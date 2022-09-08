#include "../../includes/minishell.h"

int	error(t_shell *sh, int i)
{
	if (i == 1)
	{
		sh->error = 1;
		ft_putstr_fd("MALLOC ERROR\n", 2);
	}
	if (i == 2)
	{
		sh->error = 1;
		ft_putstr_fd("COULD NOT OPEN FILE\n", 2);
	}
	if (i == 3)
	{
		sh->error = 1;
		ft_putstr_fd("COULD NOT OPEN FILE\n", 2);
		exit(130);
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
	if (i)
		return (i + 1);
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
