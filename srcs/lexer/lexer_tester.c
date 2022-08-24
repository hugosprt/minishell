#include "../../includes/minishell.h"

int size_list(t_lexer *s)
{
	t_lexer	*tmp;
	int		count;

	tmp = s;
	count = 0;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);	
}


int first_arg(t_lexer *l)
{
	t_lexer	*tmp;

	tmp = l;
	if (tmp->koi == PIPE && (tmp->next->koi == ARG || tmp->next->koi == PIPE))
		return (printf("syntax error\n"), 0);
	if (size_list(tmp) == 2)
	{
		if(tmp->koi > 0)
			return (printf("syntax error1\n"), 0);
	}
	else if (tmp->koi == PIPE && (tmp->next->koi == ARG || tmp->next->koi == PIPE))
		return (printf("syntax error\n"), 0);
	else
	{
		tmp = tmp->next;
		while (tmp && tmp->next)
		{
			if (!test_pipe(tmp))
				return (printf("syntax error\n"), 0);
			tmp = tmp->next;
		}
	}
	return (1);
}

int find_last_elem(t_lexer *l)
{
	t_lexer	*tmp;

	tmp = l;
	if (tmp == NULL)
		return (0);
	while (NULL != tmp)
	{
		if (END == tmp->next->koi)
			return (tmp->koi);
		tmp = tmp->next;
	}
	return (0);
}

int 	test_pipe(t_lexer *l)
{
	t_lexer	*tmp;

	tmp = l;
	if (find_last_elem(tmp) == PIPE)
		return (0);
	if (tmp->prev->koi == R_REDIR && tmp->koi == PIPE)
		return (0);
	if (tmp->koi == L_REDIR && tmp->next->koi == END)
		return (0);
	if (tmp->prev->koi == L_REDIR && tmp->koi == PIPE)
		return (0);
	if (tmp->prev->koi == RR_REDIR && tmp->koi == PIPE && tmp->next->koi == PIPE)
		return (0);
	if (tmp->prev->koi >= R_REDIR && tmp->koi == PIPE && tmp->next->koi == END)
		return (0);
	if (tmp->koi == PIPE && tmp->next->koi == PIPE)
		return (0);
	if (tmp->koi == LL_REDIR && tmp->next->koi == END)
		return (0);
	if (tmp->koi >= 2 && tmp->next->koi >= 2)
		return (0);
	if (tmp->koi == R_REDIR && tmp->next->koi == END)
		return (0);
	if (tmp->koi == RR_REDIR && tmp->next->koi == END)
		return (0);
	return (1);
}