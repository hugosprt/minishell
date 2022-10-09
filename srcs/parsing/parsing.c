/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpol <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:36:14 by rpol              #+#    #+#             */
/*   Updated: 2022/10/09 15:38:28 by rpol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	herenext(t_shell *sh)
{
	t_lexer	*l;

	l = sh->parsing->l;
	if (l->koi == ARG)
	{
		while (l->koi != PIPE && l->koi != END)
		{
			if (l->koi == LL_REDIR)
			{
				sh->tmp = sh->parsing->l->str;
				return (0);
			}
			l = l->next;
		}
	}
	return (1);
}

int	error(t_shell *sh, int i)
{
	sh->error = 1;
	s()->sig->ret = 1;
	if (i == 1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("MALLOC ERROR\n", 2);
		ft_exit(0, NULL, 0);
	}
	else if (herenext(sh))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(sh->parsing->l->str, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		if (i == 3)
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
	par->fd = 0;
	par->nb_pipe = count_pipe(sh->lexer);
	if (lex_check(sh))
		return (0);
	make_block(sh, sh->parsing);
	return (0);
}

int	parsing(t_shell *sh)
{
	if (!sh->lexer || sh->error == 1 || sh->lexer->koi == END)
		return (0);
	if (!sh->error)
		init_par(sh);
	return (1);
}
