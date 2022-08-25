#include "../../includes/minishell.h"


t_parsing	*parsing(t_lexer *lex)
{
	t_parsing	*par;

	if (!lex || !lex->str)
		return (NULL);
	par = init_par(lex);
	par->car = split_arg(par->arg);
	return (par);
}
