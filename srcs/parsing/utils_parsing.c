#include "../../includes/minishell.h"

static t_parsing	*first_link(t_parsing *par, t_lexer *lex)
{

	while (lex->koi != END)
	{
		if (lex->koi == R_REDIR || lex->koi == RR_REDIR)
		{
			par = redir(par, lex->next);
			lex = lex->next;
		}
		else if (lex->koi == ARG)
		{
			par->arg = ft_strjoin(par->arg, ft_strjoin(" ", lex->str));
		}
		// if (lex->koi == PIPE)
		// 	par = ft_pipe(par);
		if (lex->koi != END)
			lex = lex->next;
	}
	return (par);
}

t_parsing	*init_par(t_lexer *lex)
{
	t_parsing	*par;

	par = malloc(sizeof(t_parsing));
	par->prev = NULL;
	par->next = NULL;
	par->com = lex->str;
	par->arg = NULL;
	par->fd_out = 1;
	if (lex->next->koi == ARG)
	{
		par->arg = lex->next->str;
		first_link(par, lex->next->next);
	}
	else
		first_link(par, lex->next);
	printf("com :%s\n", par->com);
	printf("arg :%sR\n", par->arg);

	return (par);
}
