/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ici_fichier.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpol <rpol@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:42:20 by rpol              #+#    #+#             */
/*   Updated: 2022/10/08 15:03:30 by rpol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static	void	message(char *ligne, char *str, int i)
{
	if (!ligne)
	{
		ft_putstr_fd("bash: warning: here-document at line ", 2);
		ft_putnbr_fd(i, 2);
		ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("')\n", 2);
	}
}

static	void	ec145(t_parsing *p)
{
	char	*ligne;
	int		i;

	i = 1;
	p->fd = open("/tmp/.ici", O_WRONLY | O_CREAT | O_TRUNC, 00644);
	if (p->fd == -1)
		error(p->sh, 3);
	s()->t = 1;
	while (1)
	{
		ligne = readline("> ");
		if (!ligne || !strcmp(ligne, p->l->str))
		{
			message(ligne, p->l->str, i);
			break ;
		}
		ft_putendl_fd(ligne, p->fd);
		free(ligne);
		i++;
	}
	close(p->fd);
	free(ligne);
	exit(0);
}

void	ici_fichier(t_parsing *p)
{
	int		tmp_fd_out;
	int		pid;

	tmp_fd_out = dup(STDOUT_FILENO);
	dup2(p->std_out, STDOUT_FILENO);
	close(p->fd);
	dup2(p->std_in, STDIN_FILENO);
	pid = fork();
	if (pid == 0)
		ec145(p);
	p->status = 567;
	waitpid(pid, &p->status, 0);
	error_return(p, 2);
	s()->t = 0;
	p->fd = open("/tmp/.ici", O_RDONLY);
	if (p->fd == -1)
	{
		unlink("/tmp/.ici");
		ft_putstr_fd("heredoc cant be opened\n", 2);
	}
	else
		dup2_close(p->fd, STDIN_FILENO);
	dup2_close(tmp_fd_out, STDOUT_FILENO);
}
