/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpol <rpol@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:39:38 by rpol              #+#    #+#             */
/*   Updated: 2022/10/06 17:33:41 by rpol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**ft_free(char	**ret)
{
	int	k;

	k = 0;
	while (ret[k])
		k++;
	while (k >= 0)
	{
		free(ret[k]);
		k--;
	}
	free(ret);
	return (NULL);
}

void	freeenv(t_ListElement *l)
{
	t_ListElement	*tmp;
	
	ft_putstr_fd("3a\n", 2);
	while (l->next)
	{
		tmp = l;
		l = l->next;
		free(tmp->var);
		free(tmp->value);
		free(tmp);
	}
	ft_putstr_fd("3b\n", 2);
	free (l);
}


void	free_stuff(t_parsing *p, int n)
{
	t_shell	*sh;

	sh = p->sh;
	ft_free(p->arg);
	p->arg = NULL;
	p->com = NULL;
	if (n)
	{
		ft_putstr_fd("1\n", 2);
		free(sh->parsing);
		ft_putstr_fd("2\n", 2);
		freelex(sh->lexer);
		ft_putstr_fd("3\n", 2);
		//freeenv(sh->env);
		ft_putstr_fd("4\n", 2);
		free(sh);
		ft_putstr_fd("5\n", 2);
		rl_clear_history();
		ft_putstr_fd("exit\n", 2);
	}
}

int	is_n(char *str)
{
	int	a;
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[0] != '-')
	{
		return (0);
	}
	else
	{
		i++;
		a = i;
		while (str[i])
		{
			if (str[i] != 'n' || !str[i])
				return (0);
			i++;
		}
		if (i == a)
			return (0);
	}
	return (1);
}

void	echo(t_shell *shell, int i, int n)
{
	char	**str;

	str = shell->parsing->arg;
	if (str[i])
	{
		while (is_n(str[i]))
		{
			n = 0;
			i++;
		}
		if (str[i])
		{
			while (str[i])
			{
				ft_putstr_fd(str[i], 1);
				i++;
				if (str[i])
					ft_putstr_fd(" ", 1);
			}
		}
	}
	if (n == 1)
		ft_putstr_fd("\n", 1);
	s()->sig->ret = 0;
}
