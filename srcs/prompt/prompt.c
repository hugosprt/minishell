/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpol <rpol@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:44:48 by rpol              #+#    #+#             */
/*   Updated: 2022/10/03 13:44:51 by rpol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
