#include "../../includes/minishell.h"

t_parsing	*parsing(t_lexer *lex)
{
	t_parsing	*par;

	if (!lex || !lex->str)
		return (NULL);
	par = init_par(lex);
	while (lex->next)
	{
		lex = lex->next;
		par = init_par(lex);
	}
	while (par->prev)
		par = par->prev;
	return (par);
}
