/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpol <rpol@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:39:22 by rpol              #+#    #+#             */
/*   Updated: 2022/10/03 13:43:27 by rpol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strcmp_2(const char *str1, const char *str2)
{
	int	i;

	i = 0;
	if (!str1)
		return (1);
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return (1);
		i++;
	}
	if (i < ft_strlen(str1) || i < ft_strlen(str2))
		return (1);
	return (0);
}

char	*search_in_env(t_List st, char *str)
{
	t_List	tmp;

	tmp = st;
	while (tmp != NULL)
	{
		if (!ft_strcmp_2(str, tmp->var))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

void	change_pwd(t_List st, char *old)
{
	char	*cwd;
	char	*tmp;

	(void) st;
	cwd = NULL;
	cwd = getcwd(cwd, 999999);
	tmp = ft_strjoin("OLDPWD=", old);
	is_var(tmp, st);
	free(tmp);
	tmp = ft_strjoin("PWD=", cwd);
	is_var(tmp, st);
	free(tmp);
	free(cwd);
}

void	home(t_List st, char *buf)
{
	char	*home;

	home = search_in_env(st, "HOME");
	if (home)
	{
		chdir(home);
		change_pwd(st, buf);
		s()->sig->ret = 0;
	}
	else
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		s()->sig->ret = 1;
	}
	free(buf);
}

void	cd(t_List st, char *path)
{
	char	*cwd;

	cwd = NULL;
	cwd = getcwd(cwd, 999999);
	if (!cwd)
		return (path_error(path, cwd));
	if (path == NULL)
		return (home(st, cwd));
	else if (chdir(path))
	{
		return (path_error(path, cwd));
	}
	else
	{
		change_pwd(st, cwd);
		free(cwd);
		s()->sig->ret = 0;
	}
}
