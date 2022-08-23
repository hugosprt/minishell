#include "../../includes/minishell.h"

static t_lexer *create_token(t_koi	token, t_lexer *next, t_lexer *prev)
{
	t_lexer	*lexer;

	lexer = NULL;
	lexer = (t_lexer *)__malloc(sizeof(t_lexer));
	ft_bzero(lexer, sizeof(t_lexer));
	lexer->prev = prev;
	lexer->next = next;
	lexer->koi = token;
	return (lexer);
}