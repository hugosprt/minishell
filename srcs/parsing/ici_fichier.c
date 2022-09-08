#include "../../includes/minishell.h"

static	void	ec145(t_parsing *p)
{
	char	*ligne;

	p->fd = open(".ici_fichier", O_WRONLY | O_CREAT | O_TRUNC, 00600);
	if (p->fd == -1)
		error(p->sh, 3);
	s()->t = 1;
	while (1)
	{
		ligne = readline("> ");
		if (!ligne || !strcmp(ligne, p->l->str))
			break ;
		ft_putendl_fd(ligne, p->fd);
		free(ligne);
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
	dup2_close(p->std_out, STDOUT_FILENO);
	pid = fork();
	if (pid == 0)
		ec145(p);
	waitpid(pid, NULL, 0);
	p->fd = open(".ici_fichier", O_RDONLY);
	if (p->fd == -1)
		unlink(".ici_fichier");
	else
		dup2_close(p->fd, STDIN_FILENO);
	dup2_close(tmp_fd_out, STDOUT_FILENO);
}
