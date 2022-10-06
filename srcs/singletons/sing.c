/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sing.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpol <rpol@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:45:13 by rpol              #+#    #+#             */
/*   Updated: 2022/10/06 17:14:44 by rpol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_shell	*s(void)
{
	static t_shell	*s;

	if (!s)
	{
		s = malloc(sizeof(t_shell));
		s->sig = malloc(sizeof(t_sig));
		s->sig->ret = 0;
		s->t = 0;
		s->fin = 0;
	}
	return (s);
}
