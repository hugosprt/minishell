/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpol <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:39:38 by rpol              #+#    #+#             */
/*   Updated: 2022/10/09 15:45:33 by rpol             ###   ########.fr       */
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

void	freeenv(t_List l)
{
	t_List	tmp;
	int		i;

	if (s()->i)
		return ;
	i = 0;
	while (l->next)
	{	
		tmp = l;
			l = l->next;
		if (i != 0)
		{
			free(tmp->var);
			free(tmp->value);
		}
		free(tmp);
		i++;
	}
	free(l->var);
	free(l->value);
	free(l);
}

void	free_stuff(t_parsing *p, int n)
{
	t_shell	*sh;

	sh = s();
	if (p)
	{		
		ft_free(p->arg);
		p->com = NULL;
		p->arg = NULL;
	}
	if (n)
	{
		if (p)
		{
			close(p->std_in);
			close(p->std_out);
			free(p);
		}
		if (sh->lexer)
			freelex(sh->lexer);
		freeenv(sh->st);
		free(s()->sig);
		free(s());
		clear_history();
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
