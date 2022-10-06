/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpol <rpol@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:39:47 by rpol              #+#    #+#             */
/*   Updated: 2022/10/06 18:23:41 by rpol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	incr(int *i, int *r)
{
	*i += 1;
	*r = 0;
}

char	**ft_trim_equal(char const *s, char charset, int r, int k)
{
	char	**ret;
	int		j;
	int		i;

	i = 0;
	ret = malloc(sizeof(char *) * (2));
	while (s[i])
	{
		if (s[i] != charset)
		{
			j = i;
			if (r == 0)
				charset = 127;
			r++;
			while (s[j] != charset && s[j])
				j++;
			ret[++k] = ft_strcpy2(s, &i, j - i);
			if (!ret[k])
				return (ft_free_equal(ret, k));
		}
		else
			incr(&i, &r);
	}
	return (ret);
}

void	push_list_back(t_List *st, char *var_name, char *var_value)
{
	t_ListElement	*new_list;
	t_ListElement	*last;

	last = *st;
	new_list = malloc(sizeof(*new_list));
	if (new_list == NULL)
		return ;
	new_list->var = var_name;
	new_list->value = var_value;
	new_list->next = NULL;
	if (*st == NULL)
	{
		*st = new_list;
		return ;
	}
	while (last->next != NULL)
		last = last->next;
	last->next = new_list;
}

t_List	add_list(char **tab, t_List sta)
{
	int		j;
	char	**ret;
	char	*var_name;
	char	*var_value;

	j = 1;
	while (tab[j])
	{
		ret = ft_trim_equal(tab[j], '=', 1, -1);
		if (ret[0] == NULL)
		{
			ft_putstr_fd("bash: export: : not a valid identifier", 1);
			return (NULL);
		}
		else
			var_name = ret[0];
		if (ret[1] == NULL)
			var_value = " ";
		else
			var_value = ret[1];
		push_list_back(&sta, var_name, var_value);
		free(ret);
		j++;
	}	
	return (sta);
}

void	print_env(t_shell *shell, t_List st)
{
	t_List	tmp4;

	tmp4 = st;
	if (tmp4 == NULL)
		return ;
	if (shell->parsing->arg[1] != NULL)
	{
		ft_putstr_fd("too many argument\n", 2);
		s()->sig->ret = 2;
		return ;
	}
	while (tmp4 != NULL)
	{
		if (ft_strcmp(tmp4->var, "258"))
		{
			ft_putstr_fd(tmp4->var, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd(tmp4->value, 1);
			ft_putstr_fd("\n", 1);
		}
		tmp4 = tmp4->next;
	}
	free(tmp4);
	s()->sig->ret = 0;
}
