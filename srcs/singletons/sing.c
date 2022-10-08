/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sing.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpol <rpol@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:45:13 by rpol              #+#    #+#             */
/*   Updated: 2022/10/08 15:31:42 by rpol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	merror(void)
{
	ft_putstr_fd("MALLOC ERROR\n", 2);
}

t_shell	*s(void)
{
	static t_shell	*s;

	if (!s)
	{
		s = malloc(sizeof(t_shell));
		if (!s)
			return (merror(), exit(1), NULL);
		s->sig = malloc(sizeof(t_sig));
		if (!s->sig)
			return (free(s), merror(), exit(1), NULL);
		s->sig->ret = 0;
		s->t = 0;
		s->fin = 0;
	}
	return (s);
}
