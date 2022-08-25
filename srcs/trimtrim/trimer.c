#include "../../includes/minishell.h"


void	trimer(t_shell *s)
{
	t_lexer	*lexer;

	lexer = s->lexer;
	if (lexer == NULL)
		return ;
	while (lexer)
	{
		if (lexer->koi == ARG)
			trimer_large(s, lexer);
		lexer = lexer->next;
	}
}