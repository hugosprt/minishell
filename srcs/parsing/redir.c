/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpol <rpol@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:42:38 by rpol              #+#    #+#             */
/*   Updated: 2022/10/08 23:20:50 by rpol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	make_path(t_shell *sh, t_parsing *p)
{
	char		*path;
	char		**cmd_path;

	path = get_path(sh);
	if (!path)
		path_not_set(p);
	cmd_path = ft_split(path, ':');
	p->com = add_cmd(cmd_path, p->arg[0], p);
	ft_free(cmd_path);
}

void	dup2_close(int fd, int old_fd)
{
	dup2(fd, old_fd);
	close(fd);
}

static void	redir_d(t_parsing *p, int type)
{
	int	flags;
	int	fd;

	if (type == R_REDIR)
		flags = O_CREAT | O_TRUNC | O_WRONLY;
	else
		flags = O_CREAT | O_APPEND | O_WRONLY;
	fd = open(p->l->str, flags, 00644);
	if (fd == -1)
	{
		error(p->sh, 2);
		p->sh->error = 2;
	}
	else
		dup2_close(fd, 1);
}

static void	redir_g(t_parsing *p)
{
	int	fd;

	fd = open(p->l->str, O_RDONLY);
	if (fd == -1)
	{
		error(p->sh, 2);
		p->sh->error = 2;
	}
	else
		dup2_close(fd, 0);
}

t_lexer	*redir(t_parsing *p)
{
	if ((p->l->koi == R_REDIR || p->l->koi == RR_REDIR) && p->sh->error < 2)
	{
		p->l = p->l->next;
		redir_d(p, p->l->prev->koi);
	}
	else if (p->l->koi == L_REDIR && p->sh->error < 2)
	{
		p->l = p->l->next;
		redir_g(p);
	}
	else if (p->l->koi == LL_REDIR)
	{
		p->l = p->l->next;
		if (p->sh->error != 3)
			ici_fichier(p);
		if (p->sh->error == 2)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(p->sh->tmp, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
		}
	}
	p->l = p->l->next;
	return (p->l);
}
