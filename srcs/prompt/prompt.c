/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpol <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:44:48 by rpol              #+#    #+#             */
/*   Updated: 2022/10/04 15:03:59 by rpol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	isp(t_shell *sh)
{
	if (sh->lexer->koi == ARG)
	{
		if (sh->lexer->next->koi == END)
		{
			if (!ft_strcmp(sh->lexer->str, "."))
			{
				ft_putstr_fd("minishell: .: filename argument required\n", 2);
				ft_putstr_fd(".: usage: . filename [arguments]\n", 2);
				s()->sig->ret = 2;
				return (1);
			}
			if (!ft_strcmp(sh->lexer->str, ".."))
			{
				ft_putstr_fd("minishell: ..: command not found\n", 2);
				s()->sig->ret = 127;
				return (1);
			}
		}
	}
	return (0);
}

void	prompt(t_shell *s)
{
	char	*tmp;

	tmp = readline("minishell: ");
	s->prompt = tmp;
	if (s->prompt == NULL)
		ctrl_d_exit();
	if (*tmp == '\0')
		return ;
	add_history(tmp);
}
