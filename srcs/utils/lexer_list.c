#include "../../includes/minishell.h"

t_lexer	*create_token(t_koi	token, t_lexer *next, t_lexer *prev)
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

int	add_token_back(t_lexer **head, t_koi token)
{
	t_lexer	*tmp;

	if (NULL == head)
		return (0);
	tmp = (*head);
	if (NULL == tmp)
		(*head) = create_token(token, NULL, NULL);
	else
	{
		while (NULL != tmp)
		{
			if (NULL == tmp->next)
			{
				tmp->next = create_token(token, NULL, tmp);
				return (1);
			}
			tmp = tmp->next;
		}
	}
	return (1);
}
