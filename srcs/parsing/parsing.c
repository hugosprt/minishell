#include "../../includes/minishell.h"


static int cut_arg(t_parsing *par)

t_parsing	*parsing(t_lexer *lex)
{
	t_parsing	*par;

	if (!lex || !lex->str)
		return (NULL);
	par = init_par(lex);
	cut_arg(par);
	return (par);
}
